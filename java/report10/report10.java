//指定時間内複数表示
class Display_letter extends Thread{
    private String letter;
    private int time,number;
    //初期化
    public Display_letter(String l,int t,int n){
        letter = l;
        time = t;
        number = n;
    }
    //スレッド
    public void run(){
        for(int i = 0;i < number;i++){
            try {
                System.out.println(letter);
                Thread.sleep(time);
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }
}
//メイン
class Main{
    public static void main(String[] args){
        //インスタンス生成
        Display_letter display1 = new Display_letter("***",3000,10);
        Display_letter display2 = new Display_letter("======",5000,10);
        //スレッド複数実行
        display1.start();
        display2.start();

    }
}