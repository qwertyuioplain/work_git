public class DiningPhilosophers {

    // 哲学者 (箸) の数
    static final int N = 3;
    
    // 箸の配列
    static ChopStick[] chopsticks;
  
    // 哲学者の配列
    static Philosopher[] philosophers;
    
    public static void main(String[] args) {
      
      // 箸オブジェクトを N 本用意する
      chopsticks = new ChopStick[N];
      
      // オブジェクトの初期化
      for (int i = 0; i < N; i++) {
        chopsticks[i] = new ChopStick();
      }
      
      
      // 哲学者オブジェクトの生成と、
      // 各自が使える箸の登録
      philosophers = new Philosopher[N];
      
      for (int i = 0; i < N; i++) {
        philosophers[i] = new Philosopher(chopsticks[i], chopsticks[(i+1)%N]);  
      }
      
      
      // 表示用
      for (int i = 0; i < N; i++) {  
        System.out.printf("Philosopher %d         ", i);
      }
      System.out.println();
      
      for (int i = 0; i < N; i++) {  
        System.out.print("--------------------  ");
      }
      System.out.println();    
      
      // 哲学者達に食事を始めさせる。
      for (int i = 0; i < N; i++) {
        philosophers[i].start();
      }
    }
  }
  
  // 箸クラス
  class ChopStick {
    // 使用中か否か
    boolean isUsed;
  
    ChopStick() {
      isUsed = false;
    }
  }
  
  // 哲学者クラス
  class Philosopher extends Thread {
    
    static int counter = 0;
    
    // 待ち時間の最大値。適当に設定してください。
    static final long WAITTIME = 1000;
    
    // 識別番号。哲学者オブジェクトを複数作るので、
    // 表示の際に見やすいよう、各々に異なるIDを与えます。
    int number;
    
    // 自分のテリトリーにある箸。
    ChopStick leftStick;
    ChopStick rightStick;
    
    // 自分が箸を持っているか否か
    boolean hasSticks;
    
    Philosopher(ChopStick c1, ChopStick c2) {
      // IDの付与
      number = counter++;
      
      // 自分が使える箸を登録
      leftStick = c1;
      rightStick = c2;
      
      // 最初は箸を持っていない状態
      hasSticks = false;
    }
    
    // 哲学者の行動を登録したメソッド群
    
    public void run () {
      for (int i = 0; i < 5; i++) {
        // 箸を取る
        picUpSticks();
  
        // 考え事をする
        think();
        
        // 食べる
        eat();
        
        // また考える
        think();
        
        // 箸を置く
        putDownSticks();
        
        // またまた考え事をする
        think();
      }
    }
    
    // 両側の箸を一度に確保
    synchronized void picUpSticks() {
      while(leftStick.isUsed || rightStick.isUsed) {
        await();
      }
      leftStick.isUsed = true;
      printAnEvent("pick up left stick");
        
      rightStick.isUsed = true;
      printAnEvent("pick up right stick");
        
      hasSticks = true;
    }
    
    // 食事をするメソッド
    void eat() {
      if (hasSticks) {
        printAnEvent("***eating***");
        
        // ランダム時間だけ待機
        waitRandom();
      }
    }
    
    // 考え事
    void think() {
      printAnEvent("      ***thinking***");
      
      waitRandom();
    }
    
    // 2本の箸を一度に置く
    // (実際、その必要はないとは思うが、簡単のため)
    synchronized void putDownSticks() {
      if (hasSticks) {
        
        leftStick.isUsed = false;
        printAnEvent("put down left stick");
        
        rightStick.isUsed = false;
        printAnEvent("put down right stick");
        
        hasSticks = false;
      }
    }
    
    // 表示用
    void printAnEvent(String str) {
      for(int i = 0; i < 22 * number; i++) {
        System.out.print(" ");
      }
      System.out.println(str);
    }
    
    // 適当な時間だけ待つ
    void waitRandom() {
      try {
        sleep((long)(Math.random() * WAITTIME));
      } catch (InterruptedException e) { }
    }
    
    // 一瞬だけ待機
    void await() {
      try {
        sleep(1);
      } catch (InterruptedException e) { }
    }
  }