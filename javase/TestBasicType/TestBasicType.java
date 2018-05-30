public class TestBasicType {
    public static void main(String[] args) {
        //>1. print byte range
        byte aMin = 0;
        byte aMax = 0;
        for (byte i = 0; i != (byte)0xFF; ++i) {
            if (i < aMin) {
                aMin = i;
            }
            if (i > aMax) {
                aMax = i;
            }
        }
        if (aMin > (byte)0xFF) {
            aMin = (byte)0xFF;
        }
        if (aMax < (byte)0xFF) {
            aMax = (byte)0xFF;
        }
        String msg = String.format("BasicType byte range: [%d, %d]", aMin, aMax);
        System.out.println(msg);

        //>2. print short range
        TestShort.Range();
        //>3. print int range
        TestInt.Range();
        //>4. print char range
        TestChar.Range();

        //>5. automatic type cast 隐式类型转换
        int a = 1000000000;
        int b = 1000000000;
        //long c = a * b;  //ERROR
        //long c = (long)(a * b);  //ERROR
        //long c = (long)a * b;  //OK
        long c = 1L * a * b;  //OK
        //long c = a * b * 1L;  //ERROR
        System.out.print("int a = 1000000000;\nint b = 1000000000;\na * b = " + c + "*/");
    }
}

class TestShort {
    public static void Range() {
        //>2. short
        short aMin = 0;
        short aMax = 0;
        for (short i = 0; i != (short)0xFFFF; i++) {
            if (i < aMin)
                aMin = i;
            if (i > aMax)
                aMax = i;
        }
        if (aMin > (short)0xFFFF)
            aMin = (short)0xFFFF;
        if (aMax < (short)0xFFFF)
            aMax = (short)0xFFFF;
        System.out.println(String.format("BasicType short range: [%d, %d]", aMin, aMax));
    }
}

class TestInt {
    public static void Range() {
        int aMin = 0;
        int aMax = 0;
        for (int i = 0; i != 0xFFFFFFFF; i++) {
            if (i < aMin)
                aMin = i;
            if (i > aMax)
                aMax = i;
        }
        if (aMin > 0xFFFFFFFF)
            aMin = 0xFFFFFFFF;
        if (aMax < 0xFFFFFFFF)
            aMax = 0xFFFFFFFF;
        System.out.println(String.format("BasicType int range: [%d, %d]", aMin, aMax));
    }
}

class TestChar {
    public static void Range() {
        char aMin = 0;
        char aMax = 0;
        for (char i = 0; i != (char)0xFFFF; i++) {
            if (i < aMin)
                aMin = i;
            if (i > aMax)
                aMax = i;
        }
        if (aMin > (char)0xFFFF)
            aMin = (char)0xFFFF;
        if (aMax < (char)0xFFFF)
            aMax = (char)0xFFFF;
        System.out.println(String.format("BasicType char range: [%d, %d]", (int)aMin, (int)aMax));
    }

}

