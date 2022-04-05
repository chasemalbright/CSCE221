#include <iostream>
#include <vector>
#include <math.h>

using std::cout, std::endl, std::vector;


struct combination {
    int r1, r2; 
    double c1, c2;
    double w, q, req;
};


void bubbleSort(std::vector<combination>& input) {

    double temp;
    for (int i = 0; i < input.size(); i ++) {
        for (int j = 0; j < i; j++) {
            
            if (input.at(i).q < input.at(j).q) {
                temp = input.at(j).q;
                input.at(j).q = input.at(i).q;
                input.at(i).q = temp;
            }
        }
    }
}


void printcombo(combination input) {
    cout << "w: " << input.w/3.14 << "pi   q: " << input.q << " r1: " << input.r1 << "  r2: " << input.r2  << " c1: " << 
    input.c1 << " c2: " << input.c2 << endl;

}


void print(std::vector<combination> input) {
    for (int i = 0; i < input.size(); i++) {
        printcombo(input.at(i));
    }
    cout << "\n\n\n\n";
}


int main() {
    vector<int> rvals = {100, 1000, 2000, 2200, 3300, 5100, 10000, 100000, 360000, 470000};
    vector<double> cvals = {.000010, .000001, .00000047, .0000001, .000000039, .000000010, .000000005, .000000001, .00000000033};

    vector<combination> output;
    
    combination newcombo; 
    int r1, r2;
    double c1, c2;
    double req, q, w;

    for (int h = 0; h < rvals.size(); h++) {
        r1 = rvals.at(h);

        for (int i = 0; i < rvals.size(); i++) {
            r2 = rvals.at(i);
            req = (r1*r2)/(r1+r2);

            if ((r2 == 2200) || (r2 == 3300) || (r2 == 360000) || (r2 == 470000)) {
                break;
            }

            for (int j = 0; j < cvals.size(); j++) {
                if ((c2 == .000010) || (c2 == .000001) || (c2 == .000000039)) {
                    break;
                }
                c1 = cvals.at(j);

                for (int k = 0; k < cvals.size(); k++) {
                    c2 = cvals.at(k);
                    newcombo.r1 = r1;
                    newcombo.r2 = r2;
                    newcombo.c1 = c1;
                    newcombo.c2 = c2;
                    newcombo.req = req;
                    w = sqrt(1/(r1*r2*c1*c2));
                    q = sqrt((c1*req)/(c2*r1 + c2*r2));
                    newcombo.w = w;
                    newcombo.q = q;

                    if (abs((2000*3.14)-w) <= 1500) {
                        output.push_back(newcombo);
                    }
                }
            }
        }
        
    }

    vector<combination> qp1;
    vector<combination> qp25;
    vector<combination> qp5;
    vector<combination> q1;
    vector<combination> q25;


    for (int i = 0; i < output.size(); i++) {

        // q = .1
        if (abs(.1-output.at(i).q) < .1) {
            qp1.push_back(output.at(i));
        }

        // q = .25
        if (abs(.25-output.at(i).q) < .1) {
            qp25.push_back(output.at(i));
        }

        // q = .5
        if (abs(.5-output.at(i).q) < .2) {
            qp5.push_back(output.at(i));
        }

        // q = 1
        if (abs(1-output.at(i).q) < .25) {
            q1.push_back(output.at(i));
        }

        // q = 2.5
        if (abs(2.5-output.at(i).q) < .75) {
            q25.push_back(output.at(i));
        }   
    }

    // implement sort of sorts 
    bubbleSort(qp1);
    bubbleSort(qp25);
    bubbleSort(q1);
    bubbleSort(q25);
    bubbleSort(qp5);


    print(qp1);
    print(qp25);
    print(qp5);
    print(q1);
    print(q25);
    
    return 0;
}



/*
Used Vals:
w: 2242.24 q: 2.27728 r1: 5100  r2: 1000 c1: 1e-06 c2: 3.9e-08

w: 2062.84 q: 1.08242 r1: 100000  r2: 1000 c1: 4.7e-07 c2: 5e-09

w: 2357.02 q: 0.234344 r1: 360000  r2: 1000 c1: 1e-07 c2: 5e-09

w: 2051.52 q: 0.103783 r1: 360000  r2: 2000 c1: 3.3e-10 c2: 1e-06

w: 2236.07 q: 0.509516 r1: 10000  r2: 2000 c1: 1e-07 c2: 1e-07
*/