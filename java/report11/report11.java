import java.awt.*;
import java.applet.*;
import javax.swing.JButton;
import javax.swing.JFrame;

class MyApp extends JFrame{
    public MyApp(){
        setTitle("MyApp");//フレームタイトル
        setSize(300,200);//フレームサイズ
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//終了設定

        JButton b1 = new JButton();//ボタン1
        JButton b2 = new JButton();//ボタン2
        JButton b3 = new JButton();//ボタン3
        JButton b4 = new JButton();//ボタン4
        JButton b5 = new JButton();//ボタン5
        JButton b6 = new JButton();//ボタン6

        b1.setText("Button 1");
        b2.setText("Button 2");
        b3.setText("Button 3");
        b4.setText("Button 4");
        b5.setText("Button 5");
        b6.setText("Button 6");

        Container c = getContentPane();

        c.setLayout(new GridLayout(2,3));//縦2横3のGridLayoutに設定
        //ボタンを追加
        c.add(b1);
        c.add(b2);
        c.add(b3);
        c.add(b4);
        c.add(b5);
        c.add(b6);

    }
}

class Main{
    public static void main(String[] args){
        MyApp a = new MyApp();
        a.setVisible(true);
    }
}