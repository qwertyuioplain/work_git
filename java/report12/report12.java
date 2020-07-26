import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
//appクラス
class MyApp extends JFrame implements ActionListener{
    private JLabel l;
    private JButton b1,b2,b3;
    private JPanel p1,p2;

    public MyApp(){
        l = new JLabel();

        b1 = new JButton("BULE");
        b2 = new JButton("YELLOW");
        b3 = new JButton("RED");

        p1 = new JPanel();
        p2 = new JPanel();

        p1.setLayout(new GridLayout(3,1));
        p2.setLayout(new BorderLayout());

        p1.add(b1);
        p1.add(b2);
        p1.add(b3);
        p2.add(l);

        Container c = getContentPane();
        c.setLayout(new GridLayout(1,3));

        c.add(p1);
        c.add(p2);

        b1.addActionListener(this);
        b2.addActionListener(this);
        b3.addActionListener(this);
        
        l.setText("Hello World");
        l.setHorizontalAlignment(JLabel.CENTER);
    }
    //ボタンアクション
    public void actionPerformed(ActionEvent e){
        String cmd = e.getActionCommand();
        //ボタンの分岐
        if(cmd.equals("BULE")){
            l.setForeground(Color.BLUE);    
        }else if(cmd.equals("RED")){
            l.setForeground(Color.RED);
        }else if(cmd.equals("YELLOW")){
            l.setForeground(Color.YELLOW);
        }
    }
}
//メイン
class Main{
    public static void main(String[] args){
        MyApp a = new MyApp();
        a.setSize(200,100);
        a.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        a.setVisible(true);
        
    }
}