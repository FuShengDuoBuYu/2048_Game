class Term {

private:

    //coefficient(系数)
    int coef;

    //exponent(指数)
    int exp;

    //next Term
    Term *next = nullptr;

public:

    Term(int coef, int exp) : coef(coef), exp(exp) {}

    int getCoef() const {
        return coef;
    }

    int getExp() const {
        return exp;
    }

    Term *getNext() const {
        return next;
    }

    void setCoef(int coef) {
        Term::coef = coef;
    }

    void setExp(int exp) {
        Term::exp = exp;
    }

    void setNext(Term *next) {
        Term::next = next;
    }

};
