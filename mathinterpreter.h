#ifndef MATHINTERPRETER_H
#define MATHINTERPRETER_H

#include <QApplication>
#include "exceptions.h"

#include <sstream>

namespace MathInterpreter{

    int getNumberFromSymbol(char c);
    char getSymbolFromNumber(int n);

    long double QStringToNum(QString string, int base);
    QString numToQString(long double number, int base);

    QString convertToFraction(long double number, int base);

    typedef long double calcNumber;

    QString qStringFromLongDouble(const long double n);

    QString interpretToString(QString input, int base);
    long double interpretToNumber(QString input, int base);

    class Expression;

    calcNumber evaluateExpression(Expression* exp);
    Expression* parseExpression(QString input, int base);
    Expression* parseExpression(QString input, int base, int* i);

    struct Symbol{
        virtual ~Symbol(){

        }
    };

    struct SymbolNumber : Symbol{
        SymbolNumber(calcNumber n){
            this->n = n;
        }
        calcNumber n;
    };

    struct SymbolOperator : Symbol{
        SymbolOperator(QChar o){
            this->o = o;
        }
        QChar o;
    };

    struct SymbolExpression : Symbol{
        SymbolExpression(Expression* e){
            this->e = e;
        }
        virtual ~SymbolExpression();

        Expression* e;
    };

    struct SymbolFunction : Symbol{
        SymbolFunction(QString name){
            this->name = name;
            this->parameters.clear();
        }
        void addExpression(Expression* e){
            parameters.append(e);
        }
        virtual ~SymbolFunction();
        QString name = "";
        QList<Expression*> parameters;
    };

    class Expression{
    public:
        void add(Symbol* sym){
            symbols.append(sym);
        }
        void addNumber(calcNumber n){
            add(new SymbolNumber(n));
        }
        void addOperator(QChar o){
            add(new SymbolOperator(o));
        }
        void addExpression(Expression* e){
            add(new SymbolExpression(e));
        }
        void addFunction(SymbolFunction* e){
            add(e);
        }
        ~Expression(){
            qDeleteAll(symbols);
        }

        bool isParameter = false;
        QList<Symbol*> symbols;
    };
}

#endif // MATHINTERPRETER_H
