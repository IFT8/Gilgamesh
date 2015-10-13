package com.rover12421.crack.jerbrains;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;

/**
 * Created by rover12421
 */
public class Main {

    public enum Product {
        RubyMine    (1, "RubyMine"  , GenericKeyMaker.PRODUCTID_RubyMine    , "BB62FBB57F105CD61B47AE2290FCB3CE1179942DE171BEDDF6BAA1A521B9368B735C7C931902EBA8DE6D160711A6ECC40F4A5E766E9FCDEE8A38715DB572AD3D", "7BFADCB153F59E86E69BC1820B4DB72573786E6B00CB824E57AD59BFE915231972746F47C6FBE0D8D88809DA313C1E4BEAD305AD8AFD31AE116ABCB181FF4F21", true),
        PyCharm     (2, "PyCharm"   , GenericKeyMaker.PRODUCTID_PyCharm     , "D57B0596A03949D9A3BB0CD1F7931E405AE27D0E0AF4E562072B487B0DAB7F0874AA982E5383E75FF13D36CA9D8531AC1FA2ED7B11C8858E821C2D5FB48002DD", "406047D02363033D295DB7C0FD8A94DDCD4A6D71B5A622220C8D65DF0DC1409E0BDE26AF66B0AD717406C22FC8BEC3ED88C1B7091BA3443B6BFBA26120DE6A15", true),
        WebStorm    (3, "WebStorm"  , GenericKeyMaker.PRODUCTID_WebStorm    , "BB62FBB57F105CD61B47AE2290FCB3CE1179942DE171BEDDF6BAA1A521B9368B735C7C931902EBA8DE6D160711A6ECC40F4A5E766E9FCDEE8A38715DB572AD3D", "7BFADCB153F59E86E69BC1820B4DB72573786E6B00CB824E57AD59BFE915231972746F47C6FBE0D8D88809DA313C1E4BEAD305AD8AFD31AE116ABCB181FF4F21", true),
        PhpStorm    (4, "PhpStorm"  , GenericKeyMaker.PRODUCTID_PhpStorm    , "BB62FBB57F105CD61B47AE2290FCB3CE1179942DE171BEDDF6BAA1A521B9368B735C7C931902EBA8DE6D160711A6ECC40F4A5E766E9FCDEE8A38715DB572AD3D", "7BFADCB153F59E86E69BC1820B4DB72573786E6B00CB824E57AD59BFE915231972746F47C6FBE0D8D88809DA313C1E4BEAD305AD8AFD31AE116ABCB181FF4F21", true),
        AppCode     (5, "AppCode"   , GenericKeyMaker.PRODUCTID_AppCode     , "F0DD6995C4BD3223641C79C8608D74F32ED54A8BDAE468EB5AC53F1F1C8925E263F82317356BC73B1C82B520630250212416C99CB39A8B7C2611E35552E166B9", "81B5EAEF61A4B584839C26253781D63243CD4F38E3A74FAD3713B3FB7025978538F10E743456F24BB20D5792BFDCB76DB6162C3D5C77DB7B29906CBFC9114EA5", true),
        Clion       (6, "Clion"     , GenericKeyMaker.PRODUCTID_CLION       , "C4AD4C091E08E5688B81B837506EB84D103FB3B2165F62E61C74B345D28C4A0CD0BE2FADF485883D0DDD4E24AAB758716027E84D420DE525B042A70FF8174031", "6FAADD5307E4912C4C993858DFA81DA853A3778993BE50CECA35505C427138D112D75AA22924E9317270C88B164C31C17C5A43B359F21DABFE923A7482DD7401", true),
        Idea        (7, "Idea"      , GenericKeyMaker.PRODUCTID_IDEA        , "430D187DE8BB3F18FB0A986E6B7163BD", "86F71688CDD2612CA117D1F54BDAE029", false),
        ;
        private int id;
        private String name;
        private int productId;
        private String pubKey;
        private String privKey;
        private boolean isRSA;

        Product(int id, String name, int productId, String pubKey, String privKey, boolean isRSA) {
            this.id         = id;
            this.name       = name;
            this.pubKey     = pubKey;
            this.privKey    = privKey;
            this.productId  = productId;
            this.isRSA      = isRSA;
        }

        public int getId() {
            return id;
        }

        public String getName() {
            return name;
        }

        public BigInteger getPubKey() {
            return new BigInteger(pubKey, 16);
        }

        public BigInteger getPrivKey() {
            return new BigInteger(privKey, 16);
        }

        public int getProductId() {
            return productId;
        }

        public boolean isRSA() {
            return isRSA;
        }

        public static Product valueOf(int id) {
            for (Product product : Product.values()) {
                if (product.getId() == id) {
                    return product;
                }
            }

            return null;
        }

        @Override
        public String toString() {
            return id + ". " + name;
        }
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Jetbrains's Product Patch or Keygen.");
        System.out.println("Crack by Rover12421.");
        System.out.println("Http://Www.Rover12421.Com");
        System.out.println("Please support genuine(https://www.jetbrains.com).");
        printSelectProduct();
        int sel;
        Product product = null;
        while (true) {
            try {
                sel = Integer.parseInt(readLine());
                if ((product = Product.valueOf(sel)) != null) {
                    break;
                }
            } catch (Throwable e) {
            }

            System.out.println("Enter err!");
            printSelectProduct();
        }

        System.out.println("Please enter your username :");
        String userName = readLine();

        if (product == product.Clion) {
            System.out.println("Clion need patch");
            System.out.println("Please enter your Clion install path or clion.jar path :");
            String path = readLine();
            while (!ClionPatch.patch(path)) {
                System.out.println("Clion install path or clion.jar path error!");
                System.out.println("Please re-enter!");
                path = readLine();
            }
        }

        System.out.println("---------------------------------------");
        System.out.println("Product  : " + product.getName());
        System.out.println("UserName : " + userName);

        GenericKeyMaker keyMaker = new GenericKeyMaker();

        if (product.isRSA) {
            System.out.println(keyMaker.generateRSAKey(product.getPrivKey(), product.getPubKey(), GenericKeyMaker.LICENSETYPE_NON_COMMERCIAL, product.getProductId(), 1, 13, userName));
        } else {
            System.out.println(keyMaker.generateNoRSAKey(product.getPrivKey(), product.getPubKey(), GenericKeyMaker.LICENSETYPE_NON_COMMERCIAL, product.getProductId(), 1, 14, userName));
        }
    }

    private static void printSelectProduct() {
        System.out.println();
        System.out.println("Please select product:");
        for (Product product : Product.values()) {
            System.out.println(product);
        }
    }

    private static String readLine() throws IOException {
        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);
        return br.readLine();
    }
}
