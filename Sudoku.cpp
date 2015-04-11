#include "Sudoku.h"
void Sudoku::Isu(){
        int su_i[144]={4,2,6,8,7,3,9,5,1,-1,-1,-1,
                       0,0,3,9,5,0,6,0,4,-1,-1,-1,
                       9,0,1,6,2,4,8,0,0,-1,-1,-1,
                       -1,-1,-1,1,3,2,0,8,7,9,5,6,
                       -1,-1,-1,0,8,0,1,9,0,4,2,0,
                       -1,-1,-1,4,9,6,2,3,0,8,7,1,
                       1,0,0,0,4,0,-1,-1,-1,6,9,5,
                       0,0,4,0,6,0,-1,-1,-1,1,3,7,
                       6,9,5,0,1,7,-1,-1,-1,2,8,4,
                       3,1,2,-1,-1,-1,7,4,0,5,0,9,
                       7,4,8,-1,-1,-1,0,6,9,3,0,2,
                       0,6,0,-1,-1,-1,3,1,0,7,0,8};
        int ia;
        for(ia=0;ia<144;ia++){
                su_num[ia]=su_i[ia];
        }
}
void Sudoku::divide(){
        k=0;//歸零
        for(i=0;i<12;i++){
                for(j=0;j<12;j++){
                        row[i][j]=su_num[k];//平行讀入數字取得12列
                        column[j][i]=su_num[k];//i跟j的順序反過來得行
                        k++;
                }
        }
        i=0;
        j=0;
        for(k=0;k<48;k++){
                for(r=0;r<3;r++){
            divide_row[k][r]=row[i][j];//將12*12的列分割成48*3的小列，之後得16個3*3的宮
            j++;//將列的數字填入小列
            if(j==12){
                i++;
                j=0;
            }//若列數已經到終點則換列繼續填入小列
        }
        }
        k=0;//歸零
        r=0;
        for(i=0;i<16;i++){
                if(k==48)k=1;
                else if(k==49)k=2;
                else if(k==50)k=3;
                for(j=0;j<9;j++){
                        B[i][j]=divide_row[k][r];
                        r++;
                        if(r==3){
                                k=k+4;
                                r=0;
                        }//第0個小列填入後就找第4個，最後一個小列為44，再+4為48不存在所以往第1個小列繼續將數字填入宮
                }
        }//將小列填入宮(直式填入)
}
void Sudoku::GiveQuestion()
{
        Isu();
        divide();//將原有數獨矩陣分割
    int a=rand()%3;//隨機
    //轉置
    if(a==1){
        int temp[12][12];
        for(i=0;i<12;i++){
                for(j=0;j<12;j++){
                        temp[i][j]=row[i][j];
                        row[i][j]=column[i][j];
                        column[i][j]=temp[i][j];
                }
        }
    }
    //列互換
    else if(a==2){
        int tempr[12];
        int b=rand()%3;
        if(b==0){
                for(j=0;j<12;j=j+3){
                    for(i=0;i<12;i++){
                    tempr[i]=row[j][i];
                    row[j][i]=row[j+1][i];
                    row[j+1][i]=tempr[i];
                }
                }
        }//每宮12列互換
        else if(b==1){
                for(j=1;j<12;j=j+3){
                    for(i=0;i<12;i++){
                    tempr[i]=row[j][i];
                    row[j][i]=row[j+1][i];
                    row[j+1][i]=tempr[i];
                }
                }
        }//每宮23列互換
        else if(b==2){
                for(j=0;j<12;j=j+3)
                for(i=0;i<12;i++){
                    tempr[i]=row[j][i];
                    row[j][i]=row[j+2][i];
                    row[j+2][i]=tempr[i];
            }
        }//每宮的13列互換

    }
    AfterRand();//將隨機後的數獨排列
    printQ();//印出數獨
}
void Sudoku::AfterRand(){
        j=0;
        k=0;
        for(i=0;i<144;i++){
                su_num[i]=row[j][k];//將數獨矩陣由隨機後的列讀入
                k++;
                if(k==12){
                        k=0;
                        j++;
                }
        }
}
void Sudoku::printQ()
{
    i=0;
    while(i<144){
        cout<<su_num[i]<<" ";
        i++;
        if(i%12==0)cout<<endl;
        }
}
int Sudoku::Solve()
{
    int iscorrect=1;//看答案對不對
    int tput=0,ans=0;
        //tput用來記在求哪個位置的值，ans看有幾組解
    int tempN[144];//記空格數的位置
    for(i=0;i<144;i++){
        tempN[i]=0;
    }//初始化
    int count=0;//記有幾個空格
    iscorrect=checkQ();//看問題有沒有存在不可解的因素
    if(iscorrect!=0){
        tput=150;
        ans=0;
        //cout<<ans<<endl;
        return ans;
    }//若問題本身已經不可解，則ans=0表無解，tput設很大以免跑入下面的迴圈
    while(tput<144&&tput>=0){
        if(su_num[tput]==0&&tput<144)//尋找空格
        {
                count++;//若有空格則+1
                tempN[count]=tput;//矩陣紀錄空格是在數獨的第幾個位置
                su_num[tput]++;//將空格數+1
                iscorrect=check(tput);//檢查是否可以填入
            while(iscorrect!=0){
                    su_num[tput]++;//若檢查沒過再繼續+1
                    iscorrect=check(tput);//繼續檢查
                    if(su_num[tput]>9){//如果填入數>9還是過不了代表之前有可能填錯，回到上一個空格位置填數
                        su_num[tput]=0;//將正在填的位置數歸零
                        count=count-1;
                        tput=tempN[count];//回到上個位置重填
                        su_num[tput]++;//將上個位置的數+1
                        iscorrect=check(tput);//繼續檢查
                        if(count<0){
                                ans=0;
                                tput=150;
                                break;
                                        }//如果連第一個位置都填不了代表無解，跳離迴圈
                    }
            }
        }
        else if(su_num[tput]!=0){
                tput++;
        }//若已經為題目的格子就跳過直到找到下一個空格數
    }
    if(iscorrect==0)//如果都正確的話得第一個解
        {
                ans=1;//解數+1
        }
        int max=count;
        int Osu_num[144];
        int ti;
        for(ti=0;ti<144;ti++){
                Osu_num[ti]=su_num[ti];
        }
        for(ti=0;ti<=count;ti++){
        tput=tempN[ti];
        su_num[tput]=0;
    }
        tput=tempN[count];
    if(ans==1){
        while(count>0&&count<=max){
            tput=tempN[count];
            su_num[tput]++;
            iscorrect=check(tput);
            while(iscorrect!=0){
                su_num[tput]++;
                iscorrect=check(tput);
                if(su_num[tput]>9){
                        su_num[tput]=0;
                        count++;
                        tput=tempN[count];
                        su_num[tput]++;
                        iscorrect=check(tput);
                }
            }
            if(iscorrect==0){
                count--;
            }
        }
    }
    for(ti=0;ti<144;ti++){
        if(su_num[ti]!=Osu_num[ti]&&su_num[ti]!=0){
                ans=2;
        }
    }
    if(ans==0)cout<<ans<<endl;
    else if(ans==1){
         cout<<ans<<endl;
         i=0;
         while(i<144){
         cout<<Osu_num[i]<<" ";
         i++;
         if(i%12==0)cout<<endl;
         }
    }
    else if(ans==2){
         cout<<ans<<endl;
    }
    return ans;
}
int Sudoku::checkQ(){
        divide();//先將題目分割做分析
        int checkc[16][10],checkb[16][10],checkr[16][10],tempcheck,sol=0;
        int countm=0,countM=0;
        for(i=0;i<144;i++){
                if(su_num[i]==-1){
                        countm++;//計算題目有幾個-1
                }
                else if(su_num[i]>9)countM++;//計算有沒有>9的數字
        }
        if(countm!=36||countM>0){
                sol=1;
                return sol;//如果-1不是36個或有>9的數則此數獨必定無解，回傳1
        }
        for(i=0;i<16;i++){
                for(j=0;j<10;j++){
                        checkr[i][j]=0;
                    checkb[i][j]=0;
                    checkc[i][j]=0;
                }
        }//歸零
        for(i=0;i<12;i++){
                for(j=0;j<12;j++){
                        if(row[i][j]>0){
                                tempcheck=row[i][j];
                            checkr[i][tempcheck]++;
                        }//紀錄題目每列本身有沒有重複數字
            if(column[i][j]>0){
                tempcheck=column[i][j];
                            checkc[i][tempcheck]++;
            }//紀錄題目每行有無重複數字
                }
        }
        for(i=0;i<16;i++){
                for(j=0;j<9;j++){
                        if(B[i][j]>0){
                                tempcheck=B[i][j];
                           checkb[i][tempcheck]++;
                        }
                }//紀錄題目每宮有無重複數字
        }
        for(i=0;i<16;i++){
                for(j=1;j<=9;j++){
                    if(checkr[i][j]>1)sol=1;
                    else if(checkc[i][j]>1)sol=2;
                    else if(checkb[i][j]>1)sol=3;
                }
        }
        //若題目本身已經有重複數字了那此數獨必定無解，回傳
        return sol;
}
int Sudoku::check(int tput){
        divide();//將題目分割做分析
        int a,b,c,d,e,wB,N=0;
        int forcheckr[10],forcheckc[10],forcheckb[10];
        for(i=0;i<10;i++){
                forcheckr[i]=0;
                forcheckc[i]=0;
                forcheckb[i]=0;
        }//歸零
    //a到e用來尋找數獨的空格數屬於哪行哪列哪宮
    if(su_num[tput]>9||su_num[tput]==0)
    {
        N=1;
        return N;
    }
        a=tput/12;//列
        b=tput%12;//行
        c=tput/3;
        d=c/4;
        e=c%4;
        wB=e*3+e+d/3;//宮
        for(i=0;i<12;i++){
                if(row[a][i]!=-1&&row[a][i]!=0){
                        j=row[a][i];
                        forcheckr[j]=forcheckr[j]+1;
                }
        }//檢查列裡面有沒有相同的數
        for(i=0;i<12;i++){
                if(column[b][i]!=-1&&column[b][i]!=0){
                        j=column[b][i];
                        forcheckc[j]=forcheckc[j]+1;
                }
        }//檢查行裡面有沒有相同的數
        for(i=0;i<9;i++){
                if(B[wB][i]!=-1&&B[wB][i]!=0){
                        j=B[wB][i];
                        forcheckb[j]=forcheckb[j]+1;
                }
        }//檢查宮裡面有沒有相同的數
  for(i=1;i<=9;i++){
                if(forcheckb[i]>1){
                        N=1;
                }
                else if(forcheckr[i]>1){
                        N=2;
                }
                else if(forcheckc[i]>1){
                        N=3;
                }
        }
        return N;
}

void Sudoku::ReadIn(){
//      Isu();
        int getdata;
        i=0;
        while(i<144){
                cin>>getdata;
                su_num[i]=getdata;
                i++;
        }
}

