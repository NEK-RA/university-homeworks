class Task15{

  public static void recursiveReversedDigits(int n){
    if(n != 0){
      boolean neg = n < 0;
      System.out.print(neg ? (n % 10)*(-1) : n % 10);
      System.out.print(' ');
      if(neg && n / 10 == 0){
        System.out.print('-');
      }
      n /= 10;
      recursiveReversedDigits(n);
    }else{
      System.out.println();
    }
  }

  public static void main(String[] args) {
    recursiveReversedDigits(123);
    recursiveReversedDigits(654321);
    recursiveReversedDigits(-86420);
  }
}