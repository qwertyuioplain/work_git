
//成績クラス
class Seiseki implements Calc{
    private int math;
    private int english;
    //コンスタンス
    public Seiseki(int m,int e){
        math = m;
        english = e;
    }
    //抽象クラスをオーバーライド
    public int avg_calc(){
        return (math + english)/2;
    }
}
//ご飯クラス
class Gohan implements Calc{
    private int dish;
    private int salad;
    private int soup;
    //コンスタンス
    public Gohan(int d,int sa,int so){
        dish = d;
        salad = sa;
        soup = so;
    }
    //抽象クラスをオーバーライド
    public int avg_calc(){
        return (dish + salad + soup)/3;
    }

}
//ポリモーフィズム
class Perform{

    public int f(Calc a){
        return a.avg_calc();
    }
}
//インタフェース
interface Calc{
    //抽象クラス
    int avg_calc();
}
//メインクラス
class Main{
    public static void main(String[] args){
        
        Perform p = new Perform();
        //インタフェースを成績クラスのインスタンスで宣言
        Calc s = new Seiseki(100,80);

        int avg = p.f(s);

        System.out.println("成績の平均は"+avg+"点です");
        //インタフェースをご飯クラスのインスタンスで宣言
        Calc g = new Gohan(500,300,100);

        avg = p.f(g);

        System.out.println("ご飯の値段の平均は"+avg+"円です");
        
    }
}