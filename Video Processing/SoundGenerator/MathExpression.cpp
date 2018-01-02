#include "MathExpression.h"
#include "MatException.h"
#include "MathExpressionDefOps.h"
#include <tchar.h>

#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'
#define OPEN_BRACKET_PRECEDENCE -1
#define FUNCARG_SEPARATOR ','

MathExpression::MathExpression()
{
	m_isExpressionOk = false;

	// add default operators and functions

	defineOp(new AddOp());	
	defineOp(new MinusOp());	
	defineOp(new MultOp());	
	defineOp(new DivOp());	
	defineOp(new ExpOp());
	
	defineFunc(new SinFct());
	defineFunc(new CosFct());
	defineFunc(new TanFct());
	defineFunc(new SqrtFct());
	defineFunc(new MinFct());
	defineFunc(new MaxFct());
	defineFunc(new AbsFct());
	defineFunc(new RandFct());
	defineFunc(new ProbRandFct());
}

MathExpression::~MathExpression()
{	
	// delete owned operators
	int nbOps = m_opList.size();
	for( int t=0; t<nbOps; t++ )
	{
		if( m_opList[t].canDelete )
		{
			delete m_opList[t].pOp;
			m_opList[t].pOp = NULL;
		}
	}

	// delete owned functions
	int nbFuncs = m_funcList.size();
	for( t=0; t<nbFuncs; t++ )
	{
		if( m_funcList[t].canDelete )
		{
			delete m_funcList[t].pFunc;
			m_funcList[t].pFunc = NULL;
		}
	}

	clearVariables();
}

void MathExpression::defineOp(class IMathOperator *pOp, bool canDelete)
{
	SOperatorInfo opInfo;
	opInfo.pOp = pOp;	
	opInfo.canDelete = canDelete;
	m_opList.push_back(opInfo);	
}

void MathExpression::defineFunc( class IMathFunction *pFunc, bool canDelete)
{
	SFunctionInfo funcInfo;
	funcInfo.pFunc = pFunc;	
	funcInfo.canDelete = canDelete;
	m_funcList.push_back(funcInfo);
}

bool MathExpression::setExpression(const wchar_t *expr)
{	
	m_isExpressionOk = false;
	m_expression = expr;
	m_isExpressionOk =  buildExpr(expr);

	return m_isExpressionOk;
}

// clear all defined variables
void MathExpression::clearVariables()
{
	int nbVars = m_variableList.size();
	
	// delete all variable evaluator objects
	for( int t=0; t<nbVars; t++ )
	{
		delete m_variableList[t].pVarEvaluator;
		m_variableList[t].pVarEvaluator = NULL;
	}
		
	m_variableList.clear();
}

bool MathExpression::buildExpr(const wchar_t *expr)
{
	std::wstring tmpExpr = expr;

	tmpExpr = removeSpace(tmpExpr.c_str());
	parseExpression(tmpExpr.c_str());

	return true;
}

// remove all space caracters
std::wstring MathExpression::removeSpace(const wchar_t *expr)const
{
	int length = lstrlen(expr);
	std::wstring res = _T("");
	wchar_t car[2] = {0};

	for( int t=0; t<length; t++ )
	{
		if( expr[t] != ' ' )
		{
			car[0] = expr[t];
			res += car;			
		}
	}

	return res;
}


void MathExpression::parseExpression(const wchar_t *expr)
{
	m_exprStack.clear();

	int length = lstrlen(expr);
	std::wstring curWord = _T("");
	int opID;
	wchar_t curChar = 0;
	wchar_t car[2] = {0};

	// Algorithm
	// two stacks: one for operators and functions (opStack)
	// and one for the ordered expression items (exprStack).  The last item will be
	// evaluated last.
	// We want to place each expression item (op, function and value) in the correct
	// order to be evaluated later, using the operator precedence to do so.
	// The opStack is a temp stack used during the parsing step.	

	std::vector<SOPSTACKITEM> opStack;		
	bool isFct;

	for( int t=0; t<length; t++ )
	{
		curChar = expr[t];

		bool isOp = isAnOp(curChar, &opID);

		// separator character?
		if( isOp || 
			curChar == FUNCARG_SEPARATOR ||
			curChar == OPEN_BRACKET||
			curChar == CLOSE_BRACKET)
		{	
			// parse the current word
			if( curWord.size() > 0 )
			{
				SExprInfo exprInfo = parseWord(curWord.c_str(), curChar, &isFct);
				// if its a value, add it to the exprStack
				if( !isFct )
				{
					m_exprStack.push_back(exprInfo);
				}
				else
				{
					// this is a function
					SOPSTACKITEM item;
					item.precedence = MATHOP_PREC_FCT;
					item.pEval = exprInfo.pEval;					
					opStack.push_back(item);							
				}
				curWord = _T("");
			}

			if( isOp )
			{
				if( opStack.size() > 0 )
				{
					int prevOpPrecedence = opStack[opStack.size()-1].precedence;
					int curOpPrecedence;
					if( prevOpPrecedence != OPEN_BRACKET_PRECEDENCE )
					{						
						curOpPrecedence = getOp(opID)->getPrecedence();

						// destack op until op precedence > previous op.
						// the destasked op will be evaluated before.
						// if the precedence is equal, the rule is to evaluate
						// from left to right, so the previous op has greater precedence also
						while( curOpPrecedence <= prevOpPrecedence )
						{
							SExprInfo exprInfo;
							exprInfo.pEval = opStack[opStack.size()-1].pEval;
							addAndValidateToExprStack(exprInfo);								

							// remove the last op
							opStack.erase(opStack.begin()+opStack.size()-1);

							if( opStack.size() > 0 )
							{
								prevOpPrecedence = opStack[opStack.size()-1].precedence;
								if( prevOpPrecedence == OPEN_BRACKET_PRECEDENCE )
								{
									break; // open bracket halts the destacking process
								}
							}
							else
							{
								break;	// no more op in the stack
							}

						}
					}
				}

				SOPSTACKITEM item;
				item.precedence = getOp(opID)->getPrecedence();
				item.pEval = getOp(opID);					
				opStack.push_back(item);										

			}
			else if(	curChar == FUNCARG_SEPARATOR || 
						curChar == CLOSE_BRACKET)
			{
				// destack until open bracket is found
				int curOpPrecedence = opStack[opStack.size()-1].precedence;
				while( curOpPrecedence != OPEN_BRACKET_PRECEDENCE )
				{						
					SExprInfo exprInfo;
					exprInfo.pEval = opStack[opStack.size()-1].pEval;
					addAndValidateToExprStack(exprInfo);						

					// remove the last op
					opStack.erase(opStack.begin()+opStack.size()-1);

					if( opStack.size() == 0 )
					{
						std::wstring msg = _T("Missing open bracket");					
						EXCEP(msg.c_str(), _T(""))
					}

					curOpPrecedence = opStack[opStack.size()-1].precedence;
				}

				// only if we got a close bracket, we erase the open bracket.				
				if( curChar == CLOSE_BRACKET )
				{
					// erase the open bracket
					opStack.erase(opStack.begin()+opStack.size()-1);
				}
			}
			else if( curChar == OPEN_BRACKET )
			{				
				SOPSTACKITEM item;
				item.precedence = OPEN_BRACKET_PRECEDENCE;
				opStack.push_back(item);
			}
			
		}	
		else
		{
			car[0] = curChar;
			curWord += car;
		}


	}

	// parse the last word
	if( curWord.size() > 0 )
	{
		m_exprStack.push_back(parseWord(curWord.c_str(), curChar, &isFct));
		if( isFct )
		{
			// an expression cannot end with a function?! there is no argument following
			std::wstring msg = _T("Expression cannot end with a function: ");
			msg += curWord;
			EXCEP(msg.c_str(), _T(""))
		}
	}

	// destack remaining operators, beginning by the end
	int nbOps = opStack.size();

	for( t=opStack.size()-1; t>=0; t-- )
	{
		int curOpPrecedence = opStack[t].precedence;
		if( curOpPrecedence == OPEN_BRACKET_PRECEDENCE )
		{
			std::wstring msg = _T("Missing closing bracket");
			EXCEP(msg.c_str(), _T(""))
		}
		
		SExprInfo exprInfo;
		exprInfo.pEval = opStack[t].pEval;
		addAndValidateToExprStack(exprInfo);
	}			
}

// add an operator or a function on the expression stack
// Validation: evaluate the current expressionStack and see if
// some arguments are missing 
void MathExpression::addAndValidateToExprStack(const SExprInfo &info )
{
	m_exprStack.push_back(info);	
	try
	{
		m_isExpressionOk = true;	// force the evaluation
		evaluate();
		m_isExpressionOk = false;	
	}
	catch( MATExceptions )
	{	
		m_isExpressionOk = false;
		std::wstring str = _T("Invalid usage, use: ");
		str += info.pEval->getHelpString();
		EXCEP(str.c_str(), _T(""))
	}

}

// check if this character is an operator symbol
bool MathExpression::isAnOp(wchar_t c, int *pOpID)const
{
	int nbOps = m_opList.size();

	for( int t=0; t<nbOps; t++ )
	{
		if( c == m_opList[t].pOp->getSymbol() )
		{
			*pOpID = t;
			return true;
		}
	}

	return false;	// not an operator

}

// parse a word
// It can be a function, a variable or a value
MathExpression::SExprInfo MathExpression::parseWord(const wchar_t *word, wchar_t nextChar, bool *pIsFct )
{
	SExprInfo exprInfo;
	*pIsFct = false;

	// only functions are followed by an open bracket
	if( nextChar == OPEN_BRACKET )
	{
		// it's a function
		int funcID;
		if( !isAFunction(word, &funcID) )
		{
			std::wstring msg = _T("Undefined function: ");
			msg += word;
			EXCEP(msg.c_str(), _T(""))
		}

		exprInfo.isEvaluated = false;
		exprInfo.pEval = m_funcList[funcID].pFunc;
		*pIsFct = true;

		
	}
	// if only numerical characters -> value
	// so a variable name cannot be composed of numbers only
	else if( isOnlyNum(word) )
	{
		exprInfo.isEvaluated = true;
		strToVal(word, &exprInfo.val);
	}
	else
	{
		// its a variable
		exprInfo.isEvaluated = false;
		int varID;
		varID = getVarID(word);
		if( varID == -1 )
		{
			std::wstring msg = _T("Undefined variable: ");
			msg += word;
			EXCEP(msg.c_str(), _T(""))			
		}

		exprInfo.pEval = m_variableList[varID].pVarEvaluator;
	}
	
	return exprInfo;

}

// check if this word contains only numerical characters
bool MathExpression::isOnlyNum(const wchar_t *word)const
{
	int length = lstrlen(word);

	for( int t=0; t<length; t++ )
	{
		if( iswalpha(word[t]) )
		{
			return false;	// alpha character
		}
	}

	return true;
}

// convert a string value to a double value
void MathExpression::strToVal(const wchar_t *val, double *pVal)const
{
	wchar_t **pEnd=NULL;
	*pVal = wcstod(val,pEnd);
}

// check if this name corresponds to a defined function
bool MathExpression::isAFunction(const wchar_t *word, int *pFuncID)const
{
	int nbFuncs = m_funcList.size();
	for( int t=0; t<nbFuncs; t++ )
	{
		if( wcscmp(word, m_funcList[t].pFunc->getSymbol().c_str())==0 )
		{
			*pFuncID = t;
			return true;
		}

	}

	return false; // not a function

}

bool MathExpression::defineVar(const wchar_t *name, EXPR_VALTYPE *pVal)
{
	if( getVarID(name) != -1 )
	{
		return false;	// already defined
	}

	if( isOnlyNum(name) )
	{
		return false;	// invalid variable name: contains only numbers

	}

	SVariableInfo varInfo;
	varInfo.isValueSet = false;
	varInfo.name = name;
	VariableEvaluator *pVarEvaluator = new VariableEvaluator();	
	pVarEvaluator->setVal(pVal);
	varInfo.pVarEvaluator = pVarEvaluator;
	m_variableList.push_back(varInfo);

	return true;
}

int MathExpression::getVarID(const wchar_t *varName)const
{
	int nbVars = m_variableList.size();
	for( int t=0; t<nbVars; t++ )
	{
		if( wcscmp(varName, m_variableList[t].name.c_str()) == 0 )
		{
			return t;			
		}
	}

	return -1;	// variable not found
}


IMathOperator* MathExpression::getOp(int opID)const
{
	return m_opList[opID].pOp;
}
IMathFunction* MathExpression::getFunc(int funcID)const
{
	return m_funcList[funcID].pFunc;
}


EXPR_VALTYPE MathExpression::evaluate()
{	
	if( m_exprStack.size() == 0 || 	!m_isExpressionOk )
	{
		return 0;		// empty expression or expression not set!	
	}
	m_workExprStack = m_exprStack;	

	// recursively evaluate each item, beginning by the last (it will
	// also be the last to be evaluated)
	
	return evaluate( m_workExprStack.size()-1);
	
}



EXPR_VALTYPE MathExpression::evaluate(int node)
{
	SExprInfo *pExpr = &m_workExprStack[node];

	if( pExpr->isEvaluated)
	{
		return pExpr->val;
	}	

	m_popPtr = node-1;
	EXPR_VALTYPE val = pExpr->pEval->evaluate(this);
	pExpr->isEvaluated = true;
	return val;		
}


EXPR_VALTYPE MathExpression::pop()
{
	if( m_popPtr < 0 )
	{
		EXCEP(_T("stack is empty"), _T(""))
	}

	EXPR_VALTYPE val;
	SExprInfo *pExpr = &m_workExprStack[m_popPtr];


	if( pExpr->isEvaluated )
	{
		val = pExpr->val;
		m_popPtr--;				
	}
	else
	{
		val = evaluate(m_popPtr);	
	}

	

	return val;
}

std::wstring MathExpression::longToS(long val)
{
	wchar_t str[20];
	return _ltow(val, str, 10);

}

