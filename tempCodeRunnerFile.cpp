#include <iostream>
#include <math.h>
#include <string.h>
#include <iomanip>

using namespace std;

void inverse(string *str);
int main(){
    int n;
    cin>>n;
   string str[20];
    for(int i = 0 ; i<n ; i++){
        cin>>str[i];

    }
    inverse(str);



    return 0 ;
}
void inverse(string *str){
    cout<<(*(str));
    int size = sizeof(str)/sizeof('a');
    cout<<size;
    char test[size] = *str;
    


}