

public class InserSort {
    public static void  main(String[] args) {
        char[] arr = new char[]{'5','1','8','7','2','6','4','3','9','0'};

        sort(arr);
        for(char c : arr)
          System.out.println( c + " ");
    }

    /* java 不能使用泛型数组，可以使用重载 */
    public static  int sort(char[] arr) {
        char key;
        for(int i=0; i<arr.length; ++i) {
            key = arr[i];
            int j= i-1;
            while((j>=0) && (key < arr[j])) {
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = key;
        }
        return 0;
    }
}
