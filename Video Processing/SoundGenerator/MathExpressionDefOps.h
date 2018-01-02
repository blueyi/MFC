#ifndef _MATHEXPRESSIONDEFOPS_INCLUDED
#define _MATHEXPRESSIONDEFOPS_INCLUDED

#include "MathExpression.h"
#include <math.h>
#include <windows.h>

class AddOp : public IMathOperator
{
	// return the operator precedence
	virtual EMATHOP_PRECEDENCE getPrecedence(){return MATHOP_PREC_ADD;	}

	
	virtual wchar_t getSymbol(){return '+'; }

	virtual std::wstring getHelpString(){ return _T("val1 + val2"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack){ return pStack->pop() + pStack->pop(); }


};

class MinusOp : public IMathOperator
{
	// return the operator precedence
	virtual EMATHOP_PRECEDENCE getPrecedence(){return MATHOP_PREC_ADD;	}

	
	virtual wchar_t getSymbol(){return '-'; }

	virtual std::wstring getHelpString(){ return _T("val1 - val2"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack)
	{ 
		EXPR_VALTYPE v1 = pStack->pop(); 
		EXPR_VALTYPE v2 = pStack->pop(); 

		return v2 - v1; 
	}


};

class MultOp : public IMathOperator
{
	// return the operator precedence
	virtual EMATHOP_PRECEDENCE getPrecedence(){return MATHOP_PREC_MULT;	}

	
	virtual wchar_t getSymbol(){return '*'; }

	virtual std::wstring getHelpString(){ return _T("val1 * val2"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack){ return pStack->pop() * pStack->pop(); }


};

class DivOp : public IMathOperator
{
	// return the operator precedence
	virtual EMATHOP_PRECEDENCE getPrecedence(){return MATHOP_PREC_MULT;	}


	virtual wchar_t getSymbol(){return '/'; }

	virtual std::wstring getHelpString(){ return _T("val1 / val2"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack){ EXPR_VALTYPE v2 = pStack->pop(); return pStack->pop() / v2; }


};

class ExpOp : public IMathOperator
{
	// return the operator precedence
	virtual EMATHOP_PRECEDENCE getPrecedence(){return MATHOP_PREC_EXP;	}

	
	virtual wchar_t getSymbol(){return '^'; }

	virtual std::wstring getHelpString(){ return _T("val1 ^ val2"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack){ EXPR_VALTYPE v2 = pStack->pop(); return pow(pStack->pop(), v2); }


};

class SinFct : public IMathFunction
{		
	
	virtual std::wstring getSymbol(){return _T("sin"); }

	virtual std::wstring getHelpString(){ return _T("sin(x)"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack){ return sin(pStack->pop()); }

};

class CosFct : public IMathFunction
{		
	
	virtual std::wstring getSymbol(){return _T("cos"); }

	virtual std::wstring getHelpString(){ return _T("cos(x)"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack){ return cos(pStack->pop()); }

};

class TanFct : public IMathFunction
{		
	
	virtual std::wstring getSymbol(){return _T("tan"); }

	virtual std::wstring getHelpString(){ return _T("tan(x)"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack){ return tan(pStack->pop()); }

};

class SqrtFct : public IMathFunction
{		
	
	virtual std::wstring getSymbol(){return _T("sqrt"); }

	virtual std::wstring getHelpString(){ return _T("sqrt(x)"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack)
	{ 
		EXPR_VALTYPE v1 = pStack->pop();
		if( v1 < 0 )
		{
			return 0;
		}
		else
		{
			return sqrt(v1); 
		}
	}
};

class MinFct : public IMathFunction
{		
	
	virtual std::wstring getSymbol(){return _T("min"); }

	virtual std::wstring getHelpString(){ return _T("min(v1,v2)"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack)
	{ 
		EXPR_VALTYPE v1 = pStack->pop(); 
		EXPR_VALTYPE v2 = pStack->pop(); 
		return min(v1,v2); 
	}

};

class MaxFct : public IMathFunction
{		

	virtual std::wstring getSymbol(){return _T("max"); }

	virtual std::wstring getHelpString(){ return _T("max(v1,v2)"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack)
	{ 
		EXPR_VALTYPE v1 = pStack->pop(); 
		EXPR_VALTYPE v2 = pStack->pop(); 
		return max(v1,v2); 
	}
};

class AbsFct : public IMathFunction
{		

	virtual std::wstring getSymbol(){return _T("abs"); }

	virtual std::wstring getHelpString(){ return _T("abs(val)"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack)
	{ 
		EXPR_VALTYPE v1 = pStack->pop(); 		
		return fabs(v1); 
	}
};

class RandFct : public IMathFunction
{		

	virtual std::wstring getSymbol(){return _T("rand"); }

	virtual std::wstring getHelpString(){ return _T("rand() : value will be between 0-1"); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack)
	{ 				
		return rand()%10000/10000.0; 
	}
};

class ProbRandFct : public IMathFunction
{		
	
	virtual std::wstring getSymbol(){return _T("prand"); }

	virtual std::wstring getHelpString(){ return _T("rand(probabilityOfV1,v1,probabilityOfV2,v2)"  ); }
	virtual EXPR_VALTYPE evaluate(IMathExprStack *pStack)
	{ 				
		EXPR_VALTYPE v2 = pStack->pop(); 
		EXPR_VALTYPE pv2 = pStack->pop(); 

		EXPR_VALTYPE v1 = pStack->pop(); 
		EXPR_VALTYPE pv1 = pStack->pop(); 

		EXPR_VALTYPE pTotal = pv1+pv2;
		int wpV1 = (double)pv1 / (double)pTotal * 1000;

		if( rand()%1000 <= pv1 )
		{
			return v1;
		}
		else
		{
			return v2;
		}
	}
};

#endif