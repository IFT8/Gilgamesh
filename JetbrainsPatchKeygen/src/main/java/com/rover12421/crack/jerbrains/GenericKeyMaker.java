package com.rover12421.crack.jerbrains;

import java.math.BigInteger;
import java.util.Random;
import java.util.zip.CRC32;

/**
 * Created by rover12421
 */
public class GenericKeyMaker {

    public static final int LICENSETYPE_COMMERCIAL = 0;
    public static final int LICENSETYPE_NON_COMMERCIAL = 1;
    public static final int LICENSETYPE_SITE = 2;
    public static final int LICENSETYPE_OPENSOURCE = 3;
    public static final int LICENSETYPE_PERSONAL = 4;
    public static final int LICENSETYPE_YEARACADEMIC = 5;
    public static final int LICENSETYPE_CLASSROOM = 6;
    public static final int LICENSETYPE_FLOATING = 7;

    public static final int PRODUCTID_IDEA = 1;
    public static final int PRODUCTID_RubyMine = 4;
    public static final int PRODUCTID_PyCharm = 5;
    public static final int PRODUCTID_WebStorm = 6;
    public static final int PRODUCTID_PhpStorm = 7;
    public static final int PRODUCTID_AppCode = 8;
    public static final int PRODUCTID_DBIDE = 9;
    public static final int PRODUCTID_CLION = 10;

    private Random random = new Random();

    private String getLicenseId() {
        return String.format("D%sT", Integer.toString(random.nextInt(90000) + 10000));
    }

    private short getCRC(String s, int i, byte bytes[])
    {
        CRC32 crc32 = new CRC32();
        if (s != null)
        {
            for (int j = 0; j < s.length(); j++)
            {
                char c = s.charAt(j);
                crc32.update(c);
            }
        }
        crc32.update(i);
        crc32.update(i >> 8);
        crc32.update(i >> 16);
        crc32.update(i >> 24);
        for (int k = 0; k < bytes.length - 2; k++)
        {
            byte byte0 = bytes[k];
            crc32.update(byte0);
        }
        return (short) (int) crc32.getValue();
    }

    private byte[] generateKeyBytes14(int licenseType, int productId,
                                      int minorVersion, int majorVersion,
                                      String userName, int customerId) {
        byte[] keyBytes = new byte[14];
        keyBytes[0] = (byte)((licenseType << 4) + (productId & 0xFF));
        keyBytes[1] = (byte)((minorVersion << 4) + (majorVersion & 0xFF));
        long time = System.currentTimeMillis() >> 16;
        keyBytes[2] = (byte)(int)(time & 0xFF);
        keyBytes[3] = (byte)(int)(time >> 8 & 0xFF);
        keyBytes[4] = (byte)(int)(time >> 16 & 0xFF);
        keyBytes[5] = (byte)(int)(time >> 24 & 0xFF);
        long timeDiff = Long.MAX_VALUE;
        keyBytes[6] = (byte)(int)(timeDiff & 0xFF);
        keyBytes[7] = (byte)(int)(timeDiff >> 8 & 0xFF);
        keyBytes[8] = 0;
        keyBytes[9] = 1;
        keyBytes[10] = 2;
        keyBytes[11] = 3;

        int crc32 = getCRC(userName, customerId, keyBytes);
        keyBytes[12] = (byte)(crc32 & 0xFF);
        keyBytes[13] = (byte)(crc32 >> 8 & 0xFF);

        return keyBytes;
    }

    private byte[] generateKeyBytes12(int licenseType, int productId,
                                    int minorVersion, int majorVersion,
                                    String userName, int customerId) {
        byte[] keyBytes = new byte[12];
        keyBytes[0] = (byte)((licenseType << 4) + (productId & 0xFF));
        keyBytes[1] = (byte)((minorVersion << 4) + (majorVersion & 0xFF));
        long time = System.currentTimeMillis() >> 16;
        keyBytes[2] = (byte)(int)(time & 0xFF);
        keyBytes[3] = (byte)(int)(time >> 8 & 0xFF);
        keyBytes[4] = (byte)(int)(time >> 16 & 0xFF);
        keyBytes[5] = (byte)(int)(time >> 24 & 0xFF);
        long timeDiff = Long.MAX_VALUE;
        keyBytes[6] = (byte)(int)(timeDiff & 0xFF);
        keyBytes[7] = (byte)(int)(timeDiff >> 8 & 0xFF);
        keyBytes[8] = 105;
        keyBytes[9] = -59;

        int crc32 = getCRC(userName, customerId, keyBytes);
        keyBytes[10] = (byte)(crc32 & 0xFF);
        keyBytes[11] = (byte)(crc32 >> 8 & 0xFF);

        return keyBytes;
    }

    /**
     * @param biginteger
     * @return String
     */
    public static String encodeGroups(BigInteger biginteger)
    {
        BigInteger beginner1 = BigInteger.valueOf(0x39aa400L);
        StringBuilder sb = new StringBuilder();
        for (int i = 0; biginteger.compareTo(BigInteger.ZERO) != 0; i++)
        {
            int j = biginteger.mod(beginner1).intValue();
            String s1 = encodeGroup(j);
            if (i > 0)
            {
                sb.append("-");
            }
            sb.append(s1);
            biginteger = biginteger.divide(beginner1);
        }
        return sb.toString();
    }

    /**
     * @param i
     * @return
     */
    public static String encodeGroup(int i)
    {
        StringBuilder sb = new StringBuilder();
        for (int j = 0; j < 5; j++)
        {
            int k = i % 36;
            char c;
            if (k < 10)
            {
                c = (char) (48 + k);
            }
            else
            {
                c = (char) ((65 + k) - 10);
            }
            sb.append(c);
            i /= 36;
        }
        return sb.toString();
    }

    public String generateRSAKey(BigInteger privKey, BigInteger pubKey,
                                 int licenseType, int productId,
                                 int minorVersion, int majorVersion,
                                 String userName) {

        int customerId = random.nextInt(9000) + 1000;
        byte[] keyBytes = generateKeyBytes14(licenseType, productId, minorVersion, majorVersion, userName, customerId);

        RSAEncoder encoder = new RSAEncoder(privKey, pubKey, 64, false);
        String serial = encoder.encode(keyBytes);

        serial = "===== LICENSE BEGIN =====\n" + customerId + "-" + getLicenseId() + "\n" + serial + "\n===== LICENSE END =====";
        return serial;
    }


    public String generateNoRSAKey(BigInteger privKey, BigInteger pubKey,
                                 int licenseType, int productId,
                                 int minorVersion, int majorVersion,
                                 String userName) {
        int customerId = random.nextInt(9000) + 1000;
        byte[] keyBytes = generateKeyBytes12(licenseType, productId, minorVersion, majorVersion, userName, customerId);

        BigInteger k0 = new BigInteger(keyBytes);
        BigInteger k1 = k0.modPow(pubKey, privKey);
        String s0 = Integer.toString(customerId);
        String sz = "0";
        while (s0.length() != 5)
        {
            s0 = sz.concat(s0);
        }
        s0 = s0.concat("-");
        String s1 = encodeGroups(k1);
        s0 = s0.concat(s1);
        return s0;
    }
}