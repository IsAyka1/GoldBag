//
// Created by aigul on 28.03.2020.
//

#ifndef GOLDBAG_TFRACTION_H
#define GOLDBAG_TFRACTION_H

class TFraction {
    int Numerator;// числитель
    int Denominator;// знаменатель
    bool Sign;

    public:
    TFraction(int numerator, int denominator) ;
    TFraction(int integer);
    int GetNOD(int a, int b);
    int GetNOK(int a, int b);
    void GetSimple();
    TFraction operator+(TFraction operand);
    TFraction operator=(TFraction operand);
    TFraction operator=(int integer);
    TFraction operator-(TFraction operand);
    TFraction operator/(TFraction operand);
    TFraction operator*(TFraction operand);
    bool operator==(TFraction operand);
    bool operator!=(TFraction operand);
    bool operator<(TFraction operand);
    bool operator>(TFraction operand);
    bool operator>=(TFraction operand);
    bool operator<=(TFraction operand);
    friend std::ostream& operator<< (std::ostream &out, TFraction fraction);
    friend std::istream& operator>> (std::istream &in, TFraction& fraction);
};

TFraction::TFraction(int integer) : Numerator(integer), Denominator(1) {
    if(Numerator < 0) {
        Sign = true;
        Numerator = abs(Numerator);
    } else {
        Sign = false;
    }
}

TFraction::TFraction(int numerator, int denominator)
        :  Numerator(numerator), Denominator(denominator) {
    if(Numerator < 0) {
        Sign = true;\
        Numerator = abs(Numerator);
    } else {
        Sign = false;
    }
}

int TFraction::GetNOD(int a, int b) {
    a = abs(a);
    b = abs(b);
    if (a < b)
        std::swap(a, b);
    int q = a / b;
    int r = a - q * b;
    int num = b;
    while (r != 0) {
        q = num / r;
        int NewR = num - q * r;
        num = r;
        r = NewR;
    }
    return num;
}

int TFraction::GetNOK(int a, int b) {
    return a * b / GetNOD(a, b);
}

void TFraction::GetSimple(){
    int nod = GetNOD(this->Numerator, this->Denominator);
    this->Numerator = this->Numerator / nod;
    this->Denominator = this->Denominator / nod;
}

TFraction TFraction::operator+(TFraction operand) {
    TFraction res(0);
    int nok = GetNOK(this->Denominator, operand.Denominator);
    int k1 = nok / this->Denominator;
    int k2 = nok / operand.Denominator;
    this->Numerator *= this->Sign ? -1 : 1;
    operand.Numerator *= operand.Sign ? -1 : 1;
    res.Numerator = this->Numerator * k1 + operand.Numerator * k2;
    res.Denominator = nok;
    if(res.Numerator != 0) {
        res.GetSimple();
    }
    return res;
}

std::ostream & operator<<(std::ostream &out, TFraction fraction) {
    if(fraction.Numerator % fraction.Denominator == 0) {
        int res = fraction.Numerator / fraction.Denominator;
        if(fraction.Sign){
            out << "-" << res;
        } else {
            out << res;
        }
    } else {
        if(fraction.Sign){
            out << "-" << fraction.Numerator << "/" << fraction.Denominator;
        } else {
            out << fraction.Numerator << "/" << fraction.Denominator;
        }
    }
    return out;
}

std::istream& operator>>(std::istream &in, TFraction& fraction) {
    int input;
    in >> input;
    fraction = input;
    return in;
}

TFraction TFraction::operator=(TFraction operand) {
    this->Numerator = operand.Numerator;
    this->Denominator = operand.Denominator;
    return *this;
}

TFraction TFraction::operator=(int integer) {
    Numerator = integer;
    if(Numerator < 0) {
        Sign = true;
        Numerator = abs(Numerator);
    } else {
        Sign = false;
    }
    Denominator = 1;
    return *this;
}

TFraction TFraction::operator-(TFraction operand) {
    TFraction res(0);
    int nok = GetNOK(this->Denominator, operand.Denominator);
    int k1 = nok / this->Denominator;
    int k2 = nok / operand.Denominator;
    this->Numerator *= this->Sign ? -1 : 1;
    operand.Numerator *= operand.Sign ? -1 : 1;
    res.Numerator = this->Numerator * k1 - operand.Numerator * k2;
    if(res.Numerator != 0) {
        res.GetSimple();
    }
    return res;
}

TFraction TFraction::operator/(TFraction operand) {
    TFraction res(0);
    if((this->Sign && operand.Sign) || (!this->Sign && !operand.Sign)) {
        res.Sign = false;
    } else {
        res.Sign = true;
    }
    res.Numerator = this->Numerator * operand.Denominator;
    res.Denominator = operand.Numerator == 0 ? 1 : this->Denominator * operand.Numerator;
    if(res.Numerator != 0) {
        res.GetSimple();
    }
    return res;
}

TFraction TFraction::operator*(TFraction operand) {
    TFraction res(0);
    if((this->Sign && operand.Sign) || (!this->Sign && !operand.Sign)) {
        res.Sign = false;
    } else {
        res.Sign = true;
    }
    res.Numerator = this->Numerator * operand.Numerator;
    res.Denominator = this->Denominator * operand.Denominator;
    if(res.Numerator != 0) {
        res.GetSimple();
    }
    return res;
}

bool TFraction::operator==(TFraction operand) {
    return (this->Numerator == operand.Numerator) &&
           (this->Denominator == operand.Denominator) &&
           (this->Sign == operand.Sign);
}

bool TFraction::operator!=(TFraction operand) {
    return (this->Numerator != operand.Numerator) &&
           (this->Denominator != operand.Denominator) &&
           (this->Sign != operand.Sign);
}

bool TFraction::operator<(TFraction operand) {
    this->Numerator *= this->Sign ? -1 : 1;
    operand.Numerator *= operand.Sign ? -1 : 1;
    double op1 = (double)this->Numerator / this->Denominator;
    double op2 = (double)operand.Numerator / operand.Denominator;
    return op1 < op2;
}

bool TFraction::operator>(TFraction operand) {
    this->Numerator *= this->Sign ? -1 : 1;
    operand.Numerator *= operand.Sign ? -1 : 1;
    double op1 = (double)this->Numerator / this->Denominator;
    double op2 = (double)operand.Numerator / operand.Denominator;
    return op1 > op2;
}

bool TFraction::operator<=(TFraction operand) {
    this->Numerator *= this->Sign ? -1 : 1;
    operand.Numerator *= operand.Sign ? -1 : 1;
    double op1 = (double)this->Numerator / this->Denominator;
    double op2 = (double)operand.Numerator / operand.Denominator;
    return op1 <= op2;
}

bool TFraction::operator>=(TFraction operand) {
    this->Numerator *= this->Sign ? -1 : 1;
    operand.Numerator *= operand.Sign ? -1 : 1;
    double op1 = (double)this->Numerator / this->Denominator;
    double op2 = (double)operand.Numerator / operand.Denominator;
    return op1 >= op2;
}

#endif //GOLDBAG_TFRACTION_H