import junit.framework.TestCase;

import java.io.IOException;
import java.util.Random;

public class UrlRandomTest extends TestCase {

    public void testUnitTesting() throws IOException {

        randomTesting();

    }

    /*
     * Random Test Method for CS362
     */
    public void randomTesting() {
        for(int i = 0; i < 2000; i++) {
            Random random = new Random();

            String scheme = schemeGen();

            String host = stringGen(random.nextInt(10));

            String topLvlDomain = stringGen(random.nextInt(2));

            String userInfo = userInfoGen();

            int portNum = random.nextInt(65535); // Change to 4095 to debug other parts

            String path = pathGen();

            String URLtoTest = scheme + userInfo + host + ".com:" + portNum + "/" + path;

            long options = UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS;
            UrlValidator urlVal = new UrlValidator(null, null, options);

            boolean isValidResult = urlVal.isValid( URLtoTest );

            assertTrue(URLtoTest + " failed", isValidResult);

        }
    }

    /*
     * Source: How do I pick up a random string from an array of strings in Java?
     * https://www.quora.com/How-do-I-pick-up-a-random-string-from-an-array-of-strings-in-Java
     */
    public String schemeGen() {
        String[] arr={"http://", "https://", "ftp://", "file:/"};
        Random random = new Random();
        int randomNum = random.nextInt(arr.length);
        return arr[randomNum];
    }

    /*
     * Source: Generate Random Bounded String
     * https://www.baeldung.com/java-random-string
     */
    public String stringGen(int length) {
        int leftLimit = 97; // letter 'a'
        int rightLimit = 122; // letter 'z'
        int targetStringLength = length + 1;
        Random random = new Random();
        StringBuilder buffer = new StringBuilder(targetStringLength);
        for (int i = 0; i < targetStringLength; i++) {
            int randomLimitedInt = leftLimit + (int)
                    (random.nextFloat() * (rightLimit - leftLimit + 1));
            buffer.append((char) randomLimitedInt);
        }
        return buffer.toString();
    }

    public String userInfoGen() {
        Random random = new Random();

        // Randomly generate two numbers to decide if we want user info or not
        int choice1 = random.nextInt(2);

        // Choice1 is 0: No user info, return NULL
        if (choice1 == 0) {
            return "";
        }
        // Choice1 is 1: Create user info, return user name and password
        else {
            int leftLimit = 97; // letter 'a'
            int rightLimit = 122; // letter 'z'

            int userNameLength = random.nextInt(8) + 7; // User name 7-15 characters
            int passwordLength = random.nextInt(9) + 1; // Password 1-10 characters

            StringBuilder userName = new StringBuilder(userNameLength);
            for (int i = 0; i < userNameLength; i++) {
                int randomLimitedInt = leftLimit + (int)
                        (random.nextFloat() * (rightLimit - leftLimit + 1));
                userName.append((char) randomLimitedInt);
            }

            // Randomly generate two numbers to decide if we want password or not
            int choice2 = random.nextInt(2);

            // Choice1 is 0, no password, return username
            if (choice1 == 0) {
                return userName.toString() + ":@";
            }
            // choice1 is 1, make password
            else {
                StringBuilder password = new StringBuilder(userNameLength);
                for (int j = 0; j < passwordLength; j++) {
                    int randomLimited = leftLimit + (int)
                            (random.nextFloat() * (rightLimit - leftLimit + 1));
                    password.append((char) randomLimited);
                }
                return userName.toString() + ":" + password.toString() + "@";
            }
        }
    }

    public String pathGen() {
        Random random = new Random();
        int choice = random.nextInt(2);
        // choice1 is 0, no path
        if (choice == 0) {
            return "";
        }
        else {
            String name1 = stringGen(10);
            String name2 = stringGen(4);
            return name1 + "." + name2;
        }
    }
}
