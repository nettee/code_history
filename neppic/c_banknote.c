#include <stdio.h>

int min_payment_count(int cashes[], int target)
{

    int min_result = 10;

    int proper_limit[5];

    for(int i=0; i<5; i++){
        int upper_limit;
        upper_limit = target / cashes[i];
        if(upper_limit < 10){
            proper_limit[i] = upper_limit;
        } else {
            proper_limit[i] = 9;
        }
    }

    int a, b, c, d, e;
    for(a=0; a<=proper_limit[0]; a++){
        for(b=0; b<=proper_limit[0]; b++){
            for(c=0; c<=proper_limit[0]; c++){
                for(d=0; d<=proper_limit[0]; d++){
                    for(e=0; e<=proper_limit[0]; e++){
                        int each_comb[] = {a, b, c, d, e};

                        int dot = 0;
                        for(int m=0; m<5; m++){
                            dot += each_comb[m] * cashes[m];
                        }

                        if(dot == target){
                            int sumt = 0;
                            for(int x=0; x<5; x++){
                                sumt += x;
                            }
                            if(sumt < min_result){
                                min_result = sumt;
                            }
                        }
                    }
                }
            }
        }
    }

    return min_result;
}

float average_payment_count(int cashes[]){
    int allsum = 0;
    for(int target=0; target<100; target++){
        allsum += min_payment_count(cashes, target);
    }
    return allsum / 99.0;
}

int main(void){
    int cashes[5] = {1, 5, 10, 20, 50};
    double res;
    res = average_payment_count(cashes);
    printf("res: %f\n", res);
}
        
