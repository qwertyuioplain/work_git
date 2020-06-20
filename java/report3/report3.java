class ChangeStr{

    private String s;

    public ChangeStr(String i){
        
        s = i;
    
    }

    public String change(int n){
        
        String r;
        r = s.substring(n,s.length());
        r = r.toUpperCase();

        return r;
    }

}


class Main{
    public static void main(String[] args){

        ChangeStr s = new ChangeStr("hello new world");

        String s_new = s.change(0);

        System.out.println(s_new);
    }
}





































