#include<bits/stdc++.h>
using namespace std;
struct WQ{
    int order,zd,id;

    /*
    zd:
        7.62: 1
        5.56: 2
        12:   3
    
    order:
        ks:   0
        sd:   1
        ss:   2
        tj:   3
        sd:   4
    */
};
WQ wqlist[10];
struct DY{
    int type;double size;int id;
    /*
    type:
        1:  tzw
        2:  zd
    */
};
DY dylist[16];
struct PY{
    int a,b;
};
const double eps=1e-8;

double Int(double it)
{
    return (it+eps);
}

void init_wq()
{
    wqlist[0]={0,0,0};
    wqlist[1]={3,14,1};
    wqlist[2]={3,14,2};
    wqlist[3]={2,14,3};
    wqlist[4]={1,14,4};
    wqlist[5]={3,15,5};
    wqlist[6]={2,15,6};
    wqlist[7]={2,15,7};
    wqlist[8]={4,16,8};
    wqlist[9]={4,16,9};
}

void init_dy()
{
    dylist[10]={1,5,10};
    dylist[11]={1,4,11};
    dylist[12]={1,3,12};
    dylist[13]={1,2,13};
    dylist[14]={2,0.2,14};
    dylist[15]={2,0.1,15};
    dylist[16]={2,0.5,16};
}

void init()
{
    init_wq();
    init_dy();
}


//----------------------------------------------------------------

struct Item{
    int id,size,time;

    bool operator < (Item b) const
    {
        if(time!=b.time) return time>b.time;
        return size>b.size;
    }
};

struct MP{
    int type;
    //type: 1 item
    Item it;
    //type: 2 PY
    PY py;
};

MP mp[101][101];
int nx=1,ny=1;
set<Item> pack;

double now_pack_size;

int n,m,k,t;
int tx[4]={-1,1,0,0},
    ty[4]={0,0,-1,1};
Item mainW={0,1},lastW{0,1};
//todo: insert it time

void erase_zd_to(int id,int size,int time)
{
    int change=0;
    for(auto &nt:pack)
        if(nt.id==id) {change=size-nt.size,pack.erase({nt.id,nt.size,nt.time});break;};
    
    now_pack_size+=change*dylist[id].size;    //here
    if(size!=0) pack.insert({id,size,time});
}

void plus_zd(int id,int size,int time)
{
    int change=size;
    for(auto &nt:pack)
        if(nt.id==id) {size+=nt.size,pack.erase({nt.id,nt.size,nt.time});break;}
    
    now_pack_size+=change*dylist[id].size;    //here
    pack.insert({id,size,time});
}

bool item_size(int id,int size)
{
    for(auto it:pack)
    {
        if(it.id == id)
        {
            if(it.size>=size)
            {
                pack.erase({it.id,it.size,it.time});
                if(it.size-size!=0) pack.insert({it.id,it.size-size,it.time});
                now_pack_size-=Int(size*dylist[id].size);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

void go_do(int time)
{
    
        if(mp[nx][ny].type==1)
        {
            auto it=mp[nx][ny].it;
            if(it.id<=9)
            {
                if(wqlist[mainW.id].order<wqlist[it.id].order)
                    mainW=it;    //update main W
                else if(wqlist[mainW.id].order!=wqlist[it.id].order
                &&      wqlist[lastW.id].order<wqlist[it.id].order)
                    lastW=it;
            }
            else
            {
                if(Int(dylist[it.id].size*it.size)+now_pack_size<k||Int(dylist[it.id].size*it.size)+now_pack_size<=k+eps&&Int(dylist[it.id].size*it.size)+now_pack_size>=k-eps) // cap
                {
                    plus_zd(it.id,it.size,time);
                }
                else
                {
                    int needcap=Int(dylist[it.id].size*it.size)+now_pack_size-k;
                    for(auto nt:pack)
                    {
                        if(nt.id!=wqlist[mainW.id].zd&&nt.id!=wqlist[lastW.id].zd)
                        {
                            if(nt.size*dylist[nt.id].size>needcap) erase_zd_to(nt.id,(nt.size*dylist[nt.id].size-needcap)/dylist[nt.id].size,time);
                            else erase_zd_to(nt.id,0,time);
                        }
                        if(Int(dylist[it.id].size*it.size)+now_pack_size<k||Int(dylist[it.id].size*it.size)+now_pack_size>=k-eps&&Int(dylist[it.id].size*it.size)+now_pack_size<=k+eps) break;
                    }
                    if(Int(dylist[it.id].size*it.size)+now_pack_size<k||Int(dylist[it.id].size*it.size)+now_pack_size>=k-eps&&Int(dylist[it.id].size*it.size)+now_pack_size<=k+eps)
                    {
                        plus_zd(it.id,it.size,time);
                    }
                    else
                    {
                        for(auto nt:pack)
                        {
                            {
                                if(nt.size*dylist[nt.id].size>needcap) erase_zd_to(nt.id,(nt.size*dylist[nt.id].size-needcap)/dylist[nt.id].size,time);
                                else erase_zd_to(nt.id,0,time);
                            }
                            if(Int(dylist[it.id].size*it.size)+now_pack_size<k||Int(dylist[it.id].size*it.size)+now_pack_size>=k-eps&&Int(dylist[it.id].size*it.size)+now_pack_size<=k+eps) break;
                        }
                        
                        if(Int(dylist[it.id].size*it.size)+now_pack_size<k||Int(dylist[it.id].size*it.size)+now_pack_size>=k-eps&&Int(dylist[it.id].size*it.size)+now_pack_size<=k+eps)
                        {
                            plus_zd(it.id,it.size,time);
                        }
                    }
                }
            }
        }
        else
        {
            auto player=mp[nx][ny].py;
            if(!item_size(wqlist[mainW.id].zd,player.a))
            {
                if(!item_size(wqlist[lastW.id].zd,player.b))
                    cout<<nx<<" "<<ny<<endl;
                exit(0);
            }
        }

}

int main()
{
    init();
    // k:  pack cap

    cin>>n>>m>>k>>t;
    for(int i=1;i<=n*m;i++)
    {
        int x=(i-1)/n+1,y=(i+1)%n+1;
        int id,z,a;
        cin>>id;
        if(id==17)
        {
            cin>>z>>a;
            mp[x][y].type=2;
            mp[x][y].py={z,a};
        }
        else
        {
            cin>>z;
            mp[x][y].type=1;
            mp[x][y].it={id,z};
        }
    }

    int time=0;

    go_do(time);

    for(time=1;time<=t;time++)
    {
        int op;
        cin>>op;
        op--;

        nx+=tx[op];ny+=ty[op];
        go_do(time);

        // cout<<nx<<" "<<ny<<endl;
        // cout<<mainW.id<<" "<<lastW.id<<" "<<now_pack_size<<endl;
        // for(auto it:pack)
        // {
        //     cout<<it.id<<" "<<it.size<<endl;
        // }
        // cout<<"------------------------------\n";
    }
    cout<<mainW.id<<endl<<lastW.id<<endl;
    vector<pair<int,int> > v;
    for(auto it:pack)
    {
        v.push_back({it.id,it.size});
    }
    reverse(v.begin(),v.end());
    for(auto it:v)
    {
        cout<<it.first<<" "<<it.second<<endl;
    }
    return 0;
}