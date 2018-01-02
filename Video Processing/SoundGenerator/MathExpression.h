#ifndef _MATHEXPRESSION_INCLUDED
#define _MATHEXPRESSION_INCLUDED

#include <string>
#include <vector>
#include <tchar.h>


/**************************************************

  History
______________________________________________
  Date				Autor			Description
______________________________________________

  June 1, 2004		M.J.			First version

  June 16, 2004		M.J.			- Performance optimization: suppression of the
										unnessary function parameters, in order to reduce
										the call time of highly called functions like
										"evaluate".  Suppression of the unnessary used of
										vector[] accessor.  Instead, the item is accessed once and put in
										a temp variable.
										NOTE on performance: I try a non-recursive method for the evaluation, but the
											performance has decreased in release mode.  In debug, performance is really better,
											but it seems that the compiler can better optimize the recursive version...
									- BUG fixed: when poping the remaining operators at the end of the parsing step,
										the precedence was wrong.  This was an index problem.
									- Functions and operators usage validation have been put in the parsing step.  
										getHelpString is now more helpful.
									- Portability enhancement: all CComBSTR replaced by std::wstring and const wchar_t*
									

**************************************************/

// expression evaluation result type.  double should do for
// most of the use.  To change this type, replace "double" by the
// desired type and make sure there is a MathExpression::strToVal method    
// to handle this type
typedef double EXPR_VALTYPE;		

// Operator precedence "family"
// To define an operator you must specify its precedence.
// For exemple, a division operator would have a MATHOP_PREC_MULT precedence.
typedef enum _EMATHOP_PRECEDENCE
{
	MATHOP_PREC_ADD,		
	MATHOP_PREC_MULT,
	MATHOP_PREC_EXP,
	MATHOP_PREC_FCT

}EMATHOP_PRECEDENCE;

// IMathExprStack
// Interface
// Used by evaluators (operators, functions and variables) to
// get argument values.  For example, an addition operator needs
// 2 arguments: arg1 + arg2, so it calls twice the pop method.
class IMathExprStack
{
public:

	virtual ~IMathExprStack(){};
	// get the next value on the stack
	virtual EXPR_VALTYPE pop() = 0;	
};

// IMathExprEvaluator
// Interface
// Abstraction of operators, functions and varibles that
// need to be evaluated.
class IMathExprEvaluator
{
public:

	virtual ~IMathExprEvaluator(){};
	// return an usage help string
	virtual std::wstring getHelpString() = 0;
	// Ask for the evaluation.  Arguments are taken from the stack. 
	// pStack:	stack that can be used to get arguments
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack) = 0;

};

// IMathOperator
// Interface
// Operator specific
class IMathOperator : public IMathExprEvaluator
{
public:	

	virtual ~IMathOperator(){};

		
	// return the operator precedence
	virtual EMATHOP_PRECEDENCE getPrecedence() = 0;

	// return the operator name (only one character!)
	virtual wchar_t getSymbol() = 0;
	
};

// IMathFunction
// Interface
// Function specific
class IMathFunction : public IMathExprEvaluator
{
public:	

	virtual ~IMathFunction(){};
	
	// return the operator name (any length)
	virtual std::wstring getSymbol() = 0;

	
};

// MathExpression
// Parse and evaluate mathematical expressions
class MathExpression : public IMathExprStack
{
public:
	
	MathExpression();
	~MathExpression();
	
	// Define a variable and its value pointer. Must be done before
	// setting the expression.
	// At evaluation time, value will be get from this value pointer.
	// This is a mechanic used to speed up variable evaluation, and allow
	// you to manage variable values of multiple expressions easily (values
	// can be shared between multiple expression objects).
	// At anytimes during evaluation, values are assumed to be valids (valid pointers).
	// @param name:	variable name.  at least one alpha character
	// @param pVal:	variable value pointer
	// @return true if all gone right
	bool defineVar(const wchar_t *name, EXPR_VALTYPE *pVal);
	
	// Define an operator
	// @param pOp: operator object
	// @param canDelete:	indicate if the object will be owned.  If yes, then the pointer
	//						will be deleted at the MathExpression object destruction.
	void defineOp( IMathOperator *pOp, bool canDelete = true);
	
	// Define a function	
	// @param pFunc: function object
	// @param canDelete:	indicate if the object will be owned.  If yes, then the pointer
	//						will be deleted at the MathExpression object destruction.
	void defineFunc( IMathFunction *pFunc, bool canDelete = true);
	
	// Set the current math expression.
	// The expression will be preprocessed to speed up the
	// following evaluations.
	// @Exception: MATExceptions
	// @param expr: mathematical expression
	bool setExpression(const wchar_t *expr);	
	
	// Evaluate the current math expression using the current variable values
	// @Exception: MATExceptions
	EXPR_VALTYPE evaluate();

//***************************************
// IMathExprStack interface implementation
public:
	
	EXPR_VALTYPE pop();

private:

		
	struct SOperatorInfo
	{		
		IMathOperator *pOp;
		bool canDelete;

		SOperatorInfo(){pOp = NULL; canDelete = false;}

	};	
	std::vector<SOperatorInfo> m_opList;

	struct SFunctionInfo
	{
		
		IMathFunction *pFunc;
		bool canDelete;

		SFunctionInfo(){pFunc = NULL; canDelete = false;}

	};	
	std::vector<SFunctionInfo> m_funcList;

	struct SExprInfo
	{
		IMathExprEvaluator *pEval;
		EXPR_VALTYPE val;
		bool isEvaluated;
		

		SExprInfo(){isEvaluated = false; pEval = NULL; }

	};

	typedef std::vector<SExprInfo> ExprInfoStack;
	ExprInfoStack m_exprStack, m_workExprStack;

	
	class VariableEvaluator : public IMathExprEvaluator
	{
	public:

		void setVal( EXPR_VALTYPE *pVal){m_pVal = pVal; }


		virtual std::wstring getHelpString(){ return _T(""); }		 
		virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack){ return *m_pVal; }
	private:

		EXPR_VALTYPE *m_pVal;			

	};

	struct SVariableInfo
	{	
		std::wstring name;		
		EXPR_VALTYPE val;
		bool isValueSet;
		VariableEvaluator *pVarEvaluator;

		SVariableInfo(){isValueSet = false; pVarEvaluator = NULL;}

	};	

	// used in the parsing function
	typedef struct _SOPSTACKITEM
	{
		int precedence;
		IMathExprEvaluator *pEval;

	}SOPSTACKITEM;



	std::vector<SVariableInfo> m_variableList;


	std::wstring m_expression;
	int m_popPtr;	
	bool m_isExpressionOk;		// indicate if the expression can be evaluated
	
	
	bool buildExpr(const wchar_t *expr);
	void addAndValidateToExprStack(const SExprInfo &info );
	std::wstring removeSpace(const wchar_t *expr)const;
	void parseExpression(const wchar_t *expr);
	bool isAnOp(wchar_t c, int *pOpID)const;
	SExprInfo parseWord(const wchar_t *word, wchar_t nextChar, bool *pIsFct);
	bool isAFunction(const wchar_t *word, int *pFuncID)const;	
	EXPR_VALTYPE evaluate(int node);	
	bool isOnlyNum(const wchar_t *word)const;		
	IMathOperator* getOp(int opID)const;
	IMathFunction* getFunc(int funcID)const;
	std::wstring longToS(long val);
	int getVarID(const wchar_t *varName)const;
	void clearVariables(); 	

	
	// String to double conversion
	// @param val:		string value
	// @param pVal:	[out] double value
	void strToVal(const wchar_t *val, double *pVal)const;		
};



#endif