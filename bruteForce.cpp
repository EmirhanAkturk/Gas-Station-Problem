/*
    Emirhan Aktürk
    19120205058

    Belirli bir yolu minimum maliyetle gitmek için 
    durulması gereken istasyonlar problemi Brute Force çözümü.

    Test etmek için define kısmındaki 4 seçenekten hangisini kullanmak 
    istiyorsanız sadece onu yorum dışında bırakmanız yeterli.
    Random test için istasyon sayısını #ifdef _RANDOM_ içerisindeki 
    N değerini değiştirerek ayarlayabilirsiniz.Sonucun hesaplanamadığı 
    durumlarlar mevcud istasyonlar ile yolun gidilemeyeceğini göstermektedir.
*/
#include<iostream>
#include<vector>
#include<iomanip>
#include<ctime>
#include<cstdlib>

//#define _RANDOM_ //random örnek
#define _12_ //12 istasyonlu örnek
//#define _25_ //25 istasyonlu örnek
//#define _30_ //50 istasyonlu örnek


#ifdef _RANDOM_
#define N 10 //istasyon sayısı
double mList[N];
double pList[N];
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

using namespace std;

double k=50,f=100;//tek benzinle gidilebilen min ve max mesafe
double x;//gidilecek mesafe
double minCost=1000;//ilk karşılaştırılmada değiştirilmesi için büyük bir değer ile ilklendirildi
vector<int>minStations;

/*
kombinasyon kodunda aşağıdaki linkten yararlanılmıştır
https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
*/
void combinationUtil(int arr[], vector <int>data, 
					int start, int end, 
					int index, int r); 

// n:istasyon sayısı,r kaç durağa uğranacağı(kaçlı kombinasyon olduğu)
// data vectoru tek seferdeki uğranan istasyonların hepsini tutuyor
void costCombination(int arr[], int n, int r) 
{ 
    vector<int>data(r);

    combinationUtil(arr, data, 0, n-1, 0, r); 
} 


/* arr[] ---> istasyonların indekslerini tutan array
data vectoru tek seferdeki uğranan istasyonların hepsini tutuyor
start & end ---> dizinin başlangıc ve bitiş indeksi
index --->data vektoründeki mevcud index 
r ---> kaçlı kombinasyon olduğu */
void combinationUtil(int arr[], vector <int>data, 
					int start, int end, 
					int index, int r) 
{ 
	// kombinasyon tamamlandı
	if (index == r) 
	{   
        int isOk=1;
        double cost=pList[data[0]];
        for(int i=1;i<data.size();++i){//hesaplanan kombinasyon istenen durumlara uygun mu kontrol et.
            cost+=pList[data[i]];
            double dist=mList[data[i]]-mList[data[i-1]];
            if(dist <k || dist >f){
                isOk=0;
                break;
            }
        }

        if(isOk){//hesaplanan kombinasyon koşullara uygunsa hedefe ulaşıldı mı diye kontrol et
            if(x>=mList[data[data.size()-1]] &&
                x-mList[data[data.size()-1]]<=f)//kalan yolu gidecek kadar benzin varsa
                if(cost<minCost){//hedefe ulaşıldıysa maliyet önceki durumdan az mı diye kontrol et
                    minCost=cost;
                    minStations=data;//maliyet daha azsa en az maliyet için uğranacak durakları güncelle
                }          
        }            

		return; 
	} 
    /* 
    "end-i+1 >= r-index"  koşuluyla dizinin tüm elemanlarını güncelle
    İlk istasyondan başlandığı durumlarda diğer istasyonlara uğramanın
    r li kombinasyonunu hesaplar ve her seferinde tek durumda uğranan 
    istasyonların indeksini data vectorune kaydeder.
    */

	for (int i = start; i <= end && 
		end - i + 1 >= r - index; i++) 
	{ 
		data[index] = arr[i]; 
        if(data[0]==0)//Sadece başlangıcın içinde olduğu durumlar için kombinasyon hesabı yap
		    combinationUtil(arr, data, i+1, 
						end, index+1, r); 
	} 
} 

// Driver code 
int main() 
{ 
    int arr[N];//istasyonların indislerini tutan dizi
    for(int i=0;i<N;++i)
        arr[i]=i;
  
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

   x=mList[N-1]+k/2;//gidilecek yol

    cout<<"mList:";
    for(double a:mList)
        cout<<std::setw(5)<<a<<" ";
    cout<<endl;

    cout<<"pList:";
    for(double a:pList)
        cout<<std::setw(5)<<a<<" ";
    cout<<endl;

    clock_t tStart = clock();
    
    //Global min bulmak için tüm c(n,r) kombinasyonlarını kontrol et
    for(int i=1;i<=N;++i)
        costCombination(arr, N, i);
    
    clock_t runtime=clock() - tStart;
    
    if(minCost!=1000)//ilklendirilen değer değiştiyse
    {
        cout<<"Durulan istasyonlar:";
        for(int i:minStations)
            cout<<i<<" ";

        cout<<"\nMin toplam maliyet:$"<<minCost<<endl;
    }
    else
         cout<<"Mevcud istasyonlar ile bu yolu gidemezsiniz!"<<endl;

    cout<<"Time taken:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";
    
} 



