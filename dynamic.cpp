/*
    Emirhan Aktürk
    19120205058
    
    Belirli bir yolu minimum maliyetle gitmek için 
    durulması gereken istasyonlar problemi Dynamic programing çözümü.

    Test etmek için define kısmındaki 4 seçenekten hangisini kullanmak 
    istiyorsanız sadece onu yorum dışında bırakmanız yeterli.
    Random test için istasyon sayısını #ifdef _RANDOM_ içerisindeki 
    N değerini değiştirerek ayarlayabilirsiniz.Sonucun hesaplanamadığı 
    durumlarlar mevcud istasyonlar ile yolun gidilemeyeceğini göstermektedir.
*/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<vector>
#include<cmath>

#define _RANDOM_ //random örnek
//#define _12_ //12 istasyonlu örnek
//#define _25_ //25 istasyonlu örnek
//#define _30_ //50 istasyonlu örnek
//#define _50_ //50 istasyonlu örnek

#ifdef _RANDOM_
#define N 20 //istasyon sayısı
int mList[N];
int pList[N];
#endif

#ifdef _12_
#define N 12 //istasyon sayısı
double mList[N]={ 0,  29.5,    56, 114.5,   167, 227.5,   249, 281.5,   335, 372.5,   396, 451.5}; 
double pList[N]={0 , 16.1 , 17.8 , 13.4 , 18.7 , 11.4 , 18.8 , 14.3 ,  6.6 , 10.7 , 12.4 , 12.8 };
#endif

#ifdef _25_
#define N 25 //istasyon sayısı
double mList[N]={0, 61.5,  120,147.5,  161,179.5,  219,278.5,  297,321.5,  336,393.5,  426,442.5,  490,548.5,  607,661.5,  718,764.5,  799,822.5,  867,915.5,  958 };
double pList[N]={ 0, 15.4, 19.4,  5.4, 10.8,  6.6, 11.4,  7.4, 18.5,  9.2, 17.5, 14.2,  6.6, 13.2, 15.2, 17.8, 15.9, 15.3,  5.7, 19.6, 19.7,  5.1, 11.4, 12.2, 12.1}; 
#endif

#ifdef _30_
#define N 30 //istasyon sayısı
double mList[N]={0, 61.5,  111,141.5,  203,220.5,  275,312.5,  352,383.5,  418,479.5,  541,575.5,  606,656.5,  694,744.5,  776,817.5,  870,926.5,  988,1020.5, 1058,1077.5, 1120,1156.5, 1208,1240.5};
double pList[N]={ 0,  9.4,  5.2,   12,   12,  8.9, 18.2, 11.9, 14.4,  7.7,  9.2, 11.7, 18.1, 17.7,   16,  5.5, 12.2, 14.2,  9.7,  5.5,  5.1,  6.3, 14.7, 18.6, 16.9,  8.1, 11.1,   18, 14.7, 12.9}; 
#endif

#ifdef _50_
#define N 50 //istasyon sayısı
double mList[] = {0, 26.5,   48, 78.5,  124,160.5,  219,263.5,  296,312.5,  366,390.5,  447,479.5,  503,564.5,  611,645.5,  699,759.5,  794,849.5,  898,922.5,  940,963.5,  990,1006.5, 1059,1098.5, 1127,1180.5, 1205,1262.5, 1320,1337.5, 1371,1425.5, 1469,1501.5, 1536,1548.5, 1600,1634.5, 1670,1715.5, 1757,1803.5, 1846,1875.5};
double pList[] = {0, 13.5,   16, 17.3,  9.5,   12, 13.2, 16.4,  5.3, 16.4, 18.5, 19.9, 17.8, 10.1,  7.7, 10.5, 17.5, 12.1,  8.4,   16,  5.1,    7,  5.7,   15,  5.1, 11.8, 18.3, 10.5,  7.5, 12.9, 15.7, 19.8, 13.8, 19.7, 19.3, 16.2, 13.2,  7.4, 13.3,  6.3, 10.9,  6.9, 17.5, 15.9,  6.3,  5.8, 10.2, 16.2, 13.5,  9.5};
#endif


using namespace std;

vector<int>minStations;//min maliyette ugranan istasyonları tutacak
double list[N];//tüm elemanlar -1 ile ilklendirilecek

void print(const double list[]){
    if(N<=25){
        for(int i=0;i<N;++i)
            cout<<i<<setw(6);
        cout<<endl;

        for(int i=0;i<N;++i)
            cout<<"______";
        cout<<endl;

        for(int j=0;j<N;++j)
            cout<<list[j]<<setw(6);
        cout<<endl;
    }

}

void initializer(double list[]){
    for(int i=0;i<N;++i){
            list[i]=-1;
    }
}

double dynamic(double k,double f,double x){
      
    initializer(list);

    cout<<"\nGidilecek mesafe:"<<x<<"km "<<"k:"<<k<<" f:"<<f<<endl;
    
    double cost=1000;//toplam maliyet ilk bulunan daha uygun olsun diye
                      //büyük  bir değer ile ilklendirildi

    int end=0;//min cost için ugranan son istasyon indisi
    for(int i=0;i<N;++i){
    
        for(int j=i;mList[j]-mList[i]<=f;++j){//gidebildigi istasyona kadar hesapla
            double dist=mList[j]-mList[i];
            if(dist==0 && ( mList[j]>=k || pList[j]==0 )){
                if(mList[j]<=f){
                    list[j]=pList[j];
                }
           
            }
            
            if(dist<k)
                continue;
            
            if(list[i]!=-1){
                if(list[j]==-1 || pList[j]+list[i] <=list[j]){
                    list[j]=pList[j]+list[i];
                }
            }
            
            if((x-mList[j])<=f)//kalan yolu gidecek kadar benzin varsa
            {
                if(list[j]!=-1 && cost>list[j])//maliyet öncekind en daha az olduysa
                {   
                    cost=list[j];//en duşuk maliyet olarak kaydet
                    end=j;//min maliyette ugranan son istasyon indeksi
                }
            }
                
        }
 
    }
    
    for(int i=end;i>=0;--i){
        minStations.push_back(i);
        double c=list[i]-pList[i];//bu istasyona ugramadan onceki maliyeti bul
        int j=i-1;
        while(abs(list[j]-c)>=0.01 && j>=0)
            --j;

        i=j+1; 
    }
    return cost;
}


int main(){
    double k=50,f=100;//minimum 50km,maximum 100km gidebilir

#ifdef _RANDOM_
    srand(time(0));
    mList[0]=0;
    pList[0]=0;

    for(int i=1;i<N;++i){
        mList[i]=mList[i-1]+rand()%((int)(f-k))+k/4;//istasyonlar arası mesafe 1 ile f arasında olsun
    }

    for(int i=1;i<N;++i){
        pList[i]=(rand()%((int)(f+k))+k)/10;//benzin fiyatları k ile 2k+f arasında olsun
    }
#endif
   
    double x=mList[N-1]+k/2;//gidilecek yol
    
    cout<<"\nmList:";
    for(double a:mList)
        cout<<std::setw(5)<<a<<",";
    cout<<endl;

    cout<<"\npList:";
    for(double a:pList)
        cout<<std::setw(5)<<a<<",";
    cout<<endl;

    clock_t tStart = clock();

    double cost=dynamic(k,f,x);
    
    clock_t runtime=clock() - tStart;
    if(cost!=1000)//ilklendirilen değer değiştiyse
    {
        cout<<"\nDurulan istasyonlar:";
        for(int i=minStations.size()-1;i>=0;--i)
            cout<<minStations[i]<<" ";
        cout<<"\nMin toplam maliyet:$"<<cost<<endl;
    }
    else
         cout<<"Mevcud istasyonlar ile bu yolu gidemezsiniz!"<<endl;

    cout<<"Time taken:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";
    
    //print(list); //hesap yapılması için kullanılan liste
    
    return 0;
}