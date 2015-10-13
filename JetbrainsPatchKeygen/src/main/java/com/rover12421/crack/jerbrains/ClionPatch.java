package com.rover12421.crack.jerbrains;

import org.apache.commons.io.IOUtils;

import java.io.*;
import java.nio.ByteBuffer;
import java.util.zip.*;

/**
 * Created by rover12421
 */
public class ClionPatch {

    public static boolean patch(String src) throws IOException {
        String correctSrc = src.trim();
        if (!correctSrc.equals(src)) {
            System.out.println(String.format("You enter the clion path is '%s', corrected to '%s'", src, correctSrc));
            src = correctSrc;
        }
        File file = new File(src);
        if (file.isDirectory()) {
            File f = new File(file, "lib/clion.jar");
            if (f.exists()) {
                file = f;
            } else {
                f = new File(file, "clion.jar");
                if (f.exists()) {
                    file = f;
                }
            }
        }

        if (file.isDirectory() || !file.exists()) {
            System.out.println("Err : Not found clion.jar.");
            return false;
        }

        File patch = File.createTempFile("clion", "_patch.jar", file.getParentFile());

        byte[] srcKey = "8eeb1420b7d8b90aa3b95c7ff73628e46e12c19dc91531be5f517a54b042e99c17445ce7b23834a3ec80d2691b463231be43aab7e897cc334bc9b8bb9f0d55f5".getBytes();
        byte[] desKey = "c4ad4c091e08e5688b81b837506eb84d103fb3b2165f62e61c74b345d28c4a0cd0be2fadf485883d0ddd4e24aab758716027e84d420de525b042a70ff8174031".getBytes();

        boolean isPatch = false;
        boolean patched = false;
        try (
                FileInputStream fis = new FileInputStream(file);
                ZipInputStream zis = new ZipInputStream(fis);
                ZipFile zipFile = new ZipFile(file);

                FileOutputStream fos = new FileOutputStream(patch);
                ZipOutputStream zos = new ZipOutputStream(fos)
        ){

            ZipEntry entry;
            while ((entry = zis.getNextEntry()) != null) {
                ZipEntry outEntry = new ZipEntry(entry);
                try (
                        InputStream is = zipFile.getInputStream(entry)
                        ){
                    if (entry.getName().endsWith(".class")) {
                        byte[] buff = IOUtils.toByteArray(is);

                        int index = indexOf(buff, srcKey);
                        if (index > 0) {
                            System.out.println("Find Key. Patch...");
                            System.arraycopy(desKey, 0, buff, index, desKey.length);
                            CRC32 crc32 = new CRC32();
                            crc32.update(buff);
                            outEntry.setCrc(crc32.getValue());
                            isPatch = true;
                            System.out.println("If you running Clion, Please restart Clion!!!");
                        } else {
                            if (indexOf(buff, desKey) > 0) {
                                System.out.println("Patched!");
                                patched = true;
                                break;
                            }
                        }
                        zos.putNextEntry(outEntry);
                        zos.write(buff);
                        zos.closeEntry();
                    } else {
                        zos.putNextEntry(outEntry);
                        IOUtils.copy(is, zos);
                        zos.closeEntry();
                    }
                }

            }

        }

        if (patched) {
            patch.delete();
            return true;
        }

        if (isPatch) {
            file.renameTo(new File(file.getAbsolutePath() + ".bak"));
            patch.renameTo(file);
        } else {
            patch.delete();
        }

        return isPatch;

    }

    /**
     * Search the data byte array for the first occurrence
     * of the byte array pattern.
     */
    public static int indexOf(byte[] data, byte[] pattern) {
        int[] failure = computeFailure(pattern);

        int j = 0;

        for (int i = 0; i < data.length; i++) {
            while (j > 0 && pattern[j] != data[i]) {
                j = failure[j - 1];
            }
            if (pattern[j] == data[i]) {
                j++;
            }
            if (j == pattern.length) {
                return i - pattern.length + 1;
            }
        }
        return -1;
    }

    /**
     * Computes the failure function using a boot-strapping process,
     * where the pattern is matched against itself.
     */
    private static int[] computeFailure(byte[] pattern) {
        int[] failure = new int[pattern.length];

        int j = 0;
        for (int i = 1; i < pattern.length; i++) {
            while (j>0 && pattern[j] != pattern[i]) {
                j = failure[j - 1];
            }
            if (pattern[j] == pattern[i]) {
                j++;
            }
            failure[i] = j;
        }

        return failure;
    }

}
