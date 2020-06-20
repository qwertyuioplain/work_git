import java.io.*;
import java.util.*;

//盤面
class Board{
    
    private int num_f;

    public Board(int n){
        num_f = n;
    }

    public boolean check(int place){
        boolean r = false;
        if(place == num_f){ 
            r = true;
        }
        return r;
    }

    public int move(int dice,int place){
        if(place + dice<num_f){
            place += dice;
        }
        else{
            place = num_f*2 - place - dice;
        }
        return place;
    }
}

//ダイス
class Dice{

    private Random r = new Random();
    private int num;
    
    public Dice(){
        num = 0;
    }

    public int roll(){

        num = r.nextInt(6) + 1;
        
        return num; 
    }

    public int return_num(){
        return num;
    }

    public void show(){
        System.out.println("ダイスの目は"+ num +"です");
    }

}

//プレイヤー
class Player{

    private static int place;

    public Player(){
        place = 1;
    }

    public void input_place(int i){
        place = i;
    }

    public int return_place(){
        return place;
    }

    public void place_show(){
        System.out.println("場所は"+ place +"です");
    }

}

//メイン
class Main{
    public static void main(String[] args)throws IOException{

        int goal = 30;

        Dice dice = new Dice();
        Board board = new Board(goal);
        Player player1 = new Player();
        
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("---------------------------------");
        System.out.println("すごろくゲーム");
        System.out.println("ダイスを振り、"+ goal +"マスでゴールです");
        System.out.println("初期場所は１です");

        while(!board.check(player1.return_place())){

        System.out.println("---------------------------------");
            System.out.println("エンターキーでダイスを振ってください");
            String str = br.readLine();
            dice.roll();
            dice.show();
            player1.input_place(board.move(dice.return_num(),player1.return_place()));
            player1.place_show();
        }

        System.out.println("---------------------------------");
        System.out.println("ゴールしました");

    }
}