//図形クラス
class Figure{
    
    protected int height;//高さ
    protected int width;//幅
    protected int surface;//面積

    public Figure(int h,int w){
        height = h;
        width = w;
    }
    //表示
    public void show(){
        System.out.println("高さ  　　"+ height);
        System.out.println("幅　　　　"+ width);
    }

    public void s_show(){
        System.out.println("面積　　　" + surface);
    }
}
//四角サブクラス
class Rectangle extends Figure{

    public Rectangle(int h,int w){
        super(h,w);
    }
    //計算
    public void calculate(){
        surface = height*width;
    }
}

//三角サブクラス
class Triangle extends Figure{

    public Triangle(int h,int w){
        super(h,w);
    }
    //計算
    public void calculate(){
        surface = height*width/2;
    }
}


class Main{
    public static void main(String[] args){

        Rectangle r = new Rectangle(24,124);
        Triangle t = new Triangle(12,44);
        System.out.println("----四角形----");
        r.show();
        r.calculate();
        r.s_show();
        System.out.println("----三角形----");
        t.show();
        t.calculate();
        t.s_show();
    }
}