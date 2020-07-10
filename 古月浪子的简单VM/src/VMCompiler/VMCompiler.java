import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class VMCompiler {
    public static void main(String[] args) {
        if (args.length == 1) {
            try {
                BufferedReader reader = new BufferedReader(new FileReader(args[0]));
                StringBuilder builder = new StringBuilder();
                String s;
                while ((s = reader.readLine()) != null)
                    builder.append(s).append('\n');
                compile(args[0], builder.toString());
            } catch (Exception e) {
                e.printStackTrace();
                System.out.println("Compile Error!");
            }
        } else
            System.out.println("Usage: java -jar VMCompiler.jar FILE_NAME");
    }

    static void compile(String name, String codes) {
        codes = codes.replaceAll("\\r\\n", "\n");
        codes = codes.replaceAll("\\\\n", "\n");
        List<String> list = new ArrayList<>();
        int pos = -1;
        boolean inQuote = false;
        for (int cur = 0; cur < codes.length(); cur++) {
            switch (codes.charAt(cur)) {
                case ' ':
                case '\n':
                case '\t':
                    if (!inQuote) {
                        if (cur - pos > 1)
                            list.add(codes.substring(pos + 1, cur));
                        pos = cur;
                    }
                    break;
                case '\"':
                    inQuote = !inQuote;
            }
        }
        if (codes.length() - pos > 1)
            list.add(codes.substring(pos + 1));
        ByteArrayOutputStream opStream = new ByteArrayOutputStream(0);
        HashMap<String, Integer> labels = new HashMap<>();
        HashMap<Integer, String> labelsPlaceholder = new HashMap<>();
        HashMap<String, Integer> strings = new HashMap<>();
        HashMap<Integer, String> stringsPlaceholder = new HashMap<>();
        for (int i = 0; i < list.size(); i++) {
            String current = list.get(i).toLowerCase();
            String next = i < list.size() - 1 ? list.get(i + 1).toLowerCase() : "";
            String third = i < list.size() - 2 ? list.get(i + 2).toLowerCase() : "";
            switch (current) {
                case "exit":
                    opStream.write(0);
                    break;
                case "push":
                    switch (next) {
                        case "ax":
                            opStream.write(1);
                            break;
                        case "bx":
                            opStream.write(2);
                            break;
                        case "cx":
                            opStream.write(3);
                            break;
                        case "dx":
                            opStream.write(4);
                            break;
                        case "sp":
                            opStream.write(5);
                            break;
                        default:
                            opStream.write(6);
                            opStream.write(toBytes(Integer.parseInt(next)), 0, 4);
                    }
                    i++;
                    break;
                case "pop":
                    switch (next) {
                        case "ax":
                            opStream.write(7);
                            break;
                        case "bx":
                            opStream.write(8);
                            break;
                        case "cx":
                            opStream.write(9);
                            break;
                        case "dx":
                            opStream.write(10);
                            break;
                        case "sp":
                            opStream.write(11);
                    }
                    i++;
                    break;
                case "jmp":
                    opStream.write(12);
                    labelsPlaceholder.put(opStream.size(), next);
                    opStream.write(new byte[4], 0, 4);
                    i++;
                    break;
                case "je":
                    opStream.write(13);
                    labelsPlaceholder.put(opStream.size(), next);
                    opStream.write(new byte[4], 0, 4);
                    i++;
                    break;
                case "jne":
                    opStream.write(14);
                    labelsPlaceholder.put(opStream.size(), next);
                    opStream.write(new byte[4], 0, 4);
                    i++;
                    break;
                case "jg":
                    opStream.write(15);
                    labelsPlaceholder.put(opStream.size(), next);
                    opStream.write(new byte[4], 0, 4);
                    i++;
                    break;
                case "jge":
                    opStream.write(16);
                    labelsPlaceholder.put(opStream.size(), next);
                    opStream.write(new byte[4], 0, 4);
                    i++;
                    break;
                case "jl":
                    opStream.write(17);
                    labelsPlaceholder.put(opStream.size(), next);
                    opStream.write(new byte[4], 0, 4);
                    i++;
                    break;
                case "jle":
                    opStream.write(18);
                    labelsPlaceholder.put(opStream.size(), next);
                    opStream.write(new byte[4], 0, 4);
                    i++;
                    break;
                case "mov":
                    String text = i < list.size() - 2 ? list.get(i + 2) : null;
                    if (text != null && text.startsWith("\""))
                        text = text.substring(1, text.length() - 1) + '\0';
                    switch (next) {
                        case "ax":
                            switch (third) {
                                case "bx":
                                    opStream.write(19);
                                    break;
                                case "cx":
                                    opStream.write(20);
                                    break;
                                case "dx":
                                    opStream.write(21);
                                    break;
                                case "[ax]":
                                    opStream.write(22);
                                    break;
                                default:
                                    opStream.write(23);
                                    if (third.startsWith("\"")) {
                                        stringsPlaceholder.put(opStream.size(), text);
                                        opStream.write(new byte[4], 0, 4);
                                    } else
                                        opStream.write(toBytes(Integer.parseInt(third)), 0, 4);
                            }
                            break;
                        case "bx":
                            switch (third) {
                                case "ax":
                                    opStream.write(24);
                                    break;
                                case "cx":
                                    opStream.write(25);
                                    break;
                                case "dx":
                                    opStream.write(26);
                                    break;
                                case "[ax]":
                                    opStream.write(27);
                                    break;
                                default:
                                    opStream.write(28);
                                    if (third.startsWith("\"")) {
                                        stringsPlaceholder.put(opStream.size(), text);
                                        opStream.write(new byte[4], 0, 4);
                                    } else
                                        opStream.write(toBytes(Integer.parseInt(third)), 0, 4);
                            }
                            break;
                        case "cx":
                            switch (third) {
                                case "ax":
                                    opStream.write(29);
                                    break;
                                case "bx":
                                    opStream.write(30);
                                    break;
                                case "dx":
                                    opStream.write(31);
                                    break;
                                case "[ax]":
                                    opStream.write(32);
                                    break;
                                default:
                                    opStream.write(33);
                                    if (third.startsWith("\"")) {
                                        stringsPlaceholder.put(opStream.size(), text);
                                        opStream.write(new byte[4], 0, 4);
                                    } else
                                        opStream.write(toBytes(Integer.parseInt(third)), 0, 4);
                            }
                            break;
                        case "dx":
                            switch (third) {
                                case "ax":
                                    opStream.write(34);
                                    break;
                                case "bx":
                                    opStream.write(35);
                                    break;
                                case "cx":
                                    opStream.write(36);
                                    break;
                                case "[ax]":
                                    opStream.write(37);
                                    break;
                                default:
                                    opStream.write(38);
                                    if (third.startsWith("\"")) {
                                        stringsPlaceholder.put(opStream.size(), text);
                                        opStream.write(new byte[4], 0, 4);
                                    } else
                                        opStream.write(toBytes(Integer.parseInt(third)), 0, 4);
                            }
                            break;
                        case "[ax]":
                            switch (third) {
                                case "ax":
                                    opStream.write(39);
                                    break;
                                case "bx":
                                    opStream.write(40);
                                    break;
                                case "cx":
                                    opStream.write(41);
                                    break;
                                case "dx":
                                    opStream.write(42);
                                    break;
                                default:
                                    opStream.write(43);
                                    if (third.startsWith("\"")) {
                                        stringsPlaceholder.put(opStream.size(), text);
                                        opStream.write(new byte[4], 0, 4);
                                    } else
                                        opStream.write(toBytes(Integer.parseInt(third)), 0, 4);
                            }
                    }
                    i += 2;
                    break;
                case "in":
                    if ("int".equals(next))
                        opStream.write(44);
                    else if ("string".equals(next))
                        opStream.write(45);
                    i++;
                    break;
                case "out":
                    switch (next) {
                        case "char":
                            opStream.write(46);
                            break;
                        case "int":
                            opStream.write(47);
                            break;
                        case "string":
                            opStream.write(48);
                    }
                    i++;
                    break;
                case "alloc":
                    opStream.write(49);
                    break;
                case "nop":
                    opStream.write(50);
                    break;
                case "add":
                    opStream.write(51);
                    break;
                case "mul":
                    opStream.write(52);
                    break;
                case "div":
                    opStream.write(53);
                    break;
                case "and":
                    opStream.write(54);
                    break;
                case "or":
                    opStream.write(55);
                    break;
                case "xor":
                    opStream.write(56);
                    break;
                case "neg":
                    opStream.write(57);
                    break;
                case "cmp":
                    opStream.write(58);
                    break;
                default:
                    if (current.endsWith(":"))
                        labels.put(current.substring(0, current.length() - 1), opStream.size());
            }
        }
        stringsPlaceholder.forEach((integer, string) -> {
            strings.put(string, opStream.size());
            opStream.write(string.getBytes(), 0, string.length());
        });
        byte[] opBytes = opStream.toByteArray();
        labelsPlaceholder.forEach((integer, string) -> {
            byte[] bytes = toBytes(labels.get(string));
            opBytes[integer] = bytes[0];
            opBytes[integer + 1] = bytes[1];
            opBytes[integer + 2] = bytes[2];
            opBytes[integer + 3] = bytes[3];
        });
        stringsPlaceholder.forEach((integer, string) -> {
            byte[] bytes = toBytes(strings.get(string));
            opBytes[integer] = bytes[0];
            opBytes[integer + 1] = bytes[1];
            opBytes[integer + 2] = bytes[2];
            opBytes[integer + 3] = bytes[3];
        });
        try {
            FileOutputStream outputStream = new FileOutputStream(name + ".op");
            outputStream.write(opBytes);
            outputStream.flush();
            outputStream.close();
            System.out.println("Compile Successfully!");
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Compile Error!");
        }
    }

    static byte[] toBytes(int value) {
        byte[] ret = new byte[4];
        ret[0] = (byte) (value & 0xFF);
        ret[1] = (byte) ((value >> 8) & 0xFF);
        ret[2] = (byte) ((value >> 16) & 0xFF);
        ret[3] = (byte) ((value >> 24) & 0xFF);
        return ret;
    }
}