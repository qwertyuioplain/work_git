//バイト抽象クラス
class Part_time_job{
    
    protected int day;//日数
    protected int time;//時間
    protected int income;//収入

    public Part_time_job(int d,int t){
        day = d;
        time = t;
    }

    public int get_income(){

        return income;
    }
}
//塾講師サブクラス
class Tuter extends Part_time_job{

    public Tuter(int d,int t){
        super(d,t);
    }
    //月収入計算
    public int get_income(){
        income = day*300 + 1000*time;

        return income;
    }
}

//カフェサブクラス
class Cafe extends Part_time_job{

    public Cafe(int d,int t){
        super(d,t);
    }
    //月収入計算
    public int get_income(){
        income = 900*time;
        return income;
    }
}


class Main{
    public static void main(String[] args){

        Part_time_job[] job = new Part_time_job[2];

        job[0] = new Tuter(12,44);
        job[1] = new Cafe(8,24);
        
        int income = job[0].get_income() + job[1].get_income();

        System.out.println("今月のバイト収入は" + income +"円です");

    }
}