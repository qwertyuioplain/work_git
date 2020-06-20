class Student{
    
    private long student_num;
    private int english_point;
    private int math_point;
    private int average_point;

    public void input(long a,int b,int c){
        student_num = a;
        english_point = b;
        math_point = c;
    }

    private void average_calsulation(){
        average_point = (math_point + english_point)/2;
    }

    public void show(){
        average_calsulation();
        System.out.println("学籍番号は" + student_num);
        System.out.println("平均点は" + average_point);
    }

}

class Main{
    public static void main(String[] args){
        Student s;

        s = new Student();

        s.input(6118014402L,70,80);
        s.show();
    }
}