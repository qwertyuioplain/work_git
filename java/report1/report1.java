class Main{
 
    public static void main(String[] args) {
        
        short a,b,c;
        short max_num = 10;

        for(a = 0;a < max_num; a++)for(b = 0;b < max_num; b++)for(c = 0;c < max_num; c++){
            if(a*10 + b + c*10 + a == b*100 + b*10 + c){
                System.out.println("a = "+ a);
                System.out.println("b = "+ b);
                System.out.println("c = "+ c);
            }
        }
    }
}