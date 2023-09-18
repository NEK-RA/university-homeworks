import java.util.Scanner;

public class Task17 {

    public static int readMaxNumber(int max){
        Scanner in = new Scanner(System.in);
        int a = in.nextInt();
        in.nextLine();
        if (a == 0){
            return Math.max(a, max);
        }
        max = Math.max(a, max);
        int b = readMaxNumber(max);
        return Math.max(a, b);
    }

    public static void main(String[] args) {
        System.out.println("Вводите числа по одному на каждую строку. Для завершения введите 0.");
        System.out.println("Максимальное число в указанной последовательности: " + readMaxNumber(Integer.MIN_VALUE));
    }
}
