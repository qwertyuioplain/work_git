import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
//appクラス
class Myapp extends JFrame implements ActionListener{
    //変数宣言
    private JPanel p1,p2,p3;
    private JLabel l1,l2,l3,l4;
    private JTextField t1,t2;
    private JButton ok;
    private JRadioButton wo,man;
    private ButtonGroup g;
    private long bmi,w;
    //コンストラクタ
    public Myapp(){
        //パネル
        p1 = new JPanel();
        p2 = new JPanel();
        p3 = new JPanel();
        //ラジオボタン設定
        man = new JRadioButton("男");
        wo = new JRadioButton("女");
        man.setPreferredSize(new Dimension(100,50));
        man.setFont(new Font("Arial",Font.BOLD,30));
        wo.setPreferredSize(new Dimension(100,50));
        wo.setFont(new Font("Arial",Font.BOLD,30));
        //ボタン設定
        ok = new JButton("OK");
        ok.setPreferredSize(new Dimension(100,50));
        ok.setFont(new Font("Arial",Font.BOLD,24));
        ok.addActionListener(this);
        //ラベル設定
        l1 = new JLabel("身長(cm)");
        l1.setPreferredSize(new Dimension(80,100));
        l1.setFont(new Font("Arial",Font.BOLD,18));
        l2 = new JLabel("体重(kg)");
        l2.setPreferredSize(new Dimension(80,100));
        l2.setFont(new Font("Arial",Font.BOLD,18));
        l3 = new JLabel(); 
        l3.setPreferredSize(new Dimension(100,100));
        l3.setFont(new Font("Arial",Font.BOLD,24));
        l3.setHorizontalAlignment(JLabel.CENTER);
        l4 = new JLabel(); 
        l4.setPreferredSize(new Dimension(100,100));
        l4.setFont(new Font("Arial",Font.BOLD,24));
        l4.setHorizontalAlignment(JLabel.CENTER);
        //テキストフィールド設定
        t1 = new JTextField(5);
        t2 = new JTextField(5);
        t1.setPreferredSize(new Dimension(50,30));
        t1.setFont(new Font("Arial",Font.BOLD,30));
        t2.setPreferredSize(new Dimension(50,30));
        t2.setFont(new Font("Arial",Font.BOLD,30));
        //ラジオボタンをグループ化
        g = new ButtonGroup();
        g.add(man);
        g.add(wo);
        //パネル１
        p1.setLayout(new FlowLayout());
        p1.add(l1);
        p1.add(t1);
        p1.add(l2);
        p1.add(t2);
        //パネル２
        p2.setLayout(new FlowLayout());
        p2.add(man);
        p2.add(wo);
        //パネル３
        p3.add(ok);
        //ペインに追加
        Container c = getContentPane();
        c.setLayout(new GridLayout(5,1));
        c.add(p1);
        c.add(p2);
        c.add(p3);
        c.add(l3);
        c.add(l4);
    }
    //ボタンが押された時
    public void actionPerformed(ActionEvent e){
        //例外処理
        try{
            bmi = Math.round(Double.parseDouble(t2.getText())/Math.pow((Double.parseDouble(t1.getText())/100),2));//BMI計算
            if(man.isSelected()==true){ //男の場合
                w = Math.round(Math.pow(Double.parseDouble(t1.getText())/100,2)*21.5);
                l3.setText("あなたのBMIは"+String.valueOf(bmi)+"です");    
                l4.setText("あなたの理想体重は"+String.valueOf(w)+"kgです");    
            }else if(wo.isSelected()==true){//女の場合
                w = Math.round(Math.pow(Double.parseDouble(t1.getText())/100,2)*19.0);
                l3.setText("あなたのBMIは"+String.valueOf(bmi)+"です");    
                l4.setText("あなたの理想体重は"+String.valueOf(w)+"kgです");    
            }else{
                l3.setText("性別を選択してください");//性別が選択されていない場合
            }
        }
        catch(NumberFormatException a){//数値が入ってない場合の例外処理
            l3.setText("正確な値を入力してください");
        }
    }
}

class Main{
    public static void main(String[] args){
        Myapp a = new Myapp();
        a.setSize(600,400);
        a.setTitle("BMI Calculator");
        a.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        a.setVisible(true);
    }
}