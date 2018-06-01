/*
 * @(#)TestJavaDoc.java 　　1.82 99/03/18
 *
 * Copyright (c) 1994-1999 Sun Microsystems, Inc. 901 San Antonio 　
 * Road, Palo Alto, California, 94303, U.S.A.All rights reserved.
 *
 *
 * This software is the confidential and proprietary information of Sun
 * Microsystems, Inc. (“Confidential Information”). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered into
 * with Sun.
 */

import java.io.*;


/**
* 这里是简要说明部分.
* <p>这里是详细说明部分, 这个类演示了文档注释.<br>
* 详细说明部分应该对属性或者方法进行详细的说明, 在格式上没有什么特殊的要求.
*
* @author Author
* @version 1.2
*/
public class TestJavaDoc {
   /**
   * This method returns the square of num.
   * This is a multiline description. You can use
   * as many lines as you like.
   * @param num The value to be squared.
   * @return num squared.
   */
   public double square(double num) {
      return num * num;
   }
   /**
   * This method inputs a number from the user.
   * @return The value input as a double.
   * @exception IOException On input error.
   * @see IOException
   */
   public double getNumber() throws IOException {
      InputStreamReader isr = new InputStreamReader(System.in);
      BufferedReader inData = new BufferedReader(isr);
      String str;
      str = inData.readLine();
      return (new Double(str)).doubleValue();
   }
   /**
   * This method demonstrates square().
   * @param args Unused.
   * @exception IOException On input error.
   * @see IOException
   */
   public static void main(String args[]) throws IOException
   {
      TestJavaDoc ob = new TestJavaDoc();
      double val;
      System.out.println("Enter value to be squared: ");
      val = ob.getNumber();
      val = ob.square(val);
      System.out.println("Squared value is " + val);
   }
}
