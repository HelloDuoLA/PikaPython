#include "test_common.h"
TEST_START
#if PIKA_SYNTAX_SLICE_ENABLE
TEST(stddata, test1) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    pikaVM_runSingleFile(pikaMain, "test/python/builtins/dict.py");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "{'list': [1, 2, 3], 'len': 3}\r\n");
    EXPECT_STREQ(log_buff[1], "dict_keys(['a', 'b', 'c'])\r\n");
    EXPECT_STREQ(log_buff[2], "c\r\n");
    EXPECT_STREQ(log_buff[3], "b\r\n");
    EXPECT_STREQ(log_buff[4], "a\r\n");
    EXPECT_STREQ(log_buff[5], "c\r\n");
    EXPECT_STREQ(log_buff[6], "b\r\n");
    EXPECT_STREQ(log_buff[7], "a\r\n");
    EXPECT_STREQ(log_buff[8], "{'a': 1, 'b': 2, 'c': 'test'}\r\n");
    EXPECT_STREQ(log_buff[9], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}
#endif

#if !PIKA_NANO_ENABLE
/* test b2a_hex */
TEST(stddata, test2) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "import binascii\n"
            "res = binascii.b2a_hex(b'德卡科技').decode()\n");
    /* collect */
    char* res = obj_getStr(pikaMain, "res");
    /* assert */
    EXPECT_STREQ(res, "E5BEB7E58DA1E7A791E68A80");
    /* deinit */
    obj_deinit(pikaMain);
}

/* test a2b_hex */
TEST(stddata, a2b_hex) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "import binascii\n"
            "text = binascii.a2b_hex('e4b8ade69687e6b58be8af95e794a8e4be8b')\n"
            "res = text.decode()\n");
    /* collect */
    char* res = obj_getStr(pikaMain, "res");
    /* assert */
    EXPECT_STREQ(res, "中文测试用例");
    /* deinit */
    obj_deinit(pikaMain);
}
#endif

#if PIKA_SYNTAX_IMPORT_EX_ENABLE
TEST(stddata, encode_decode) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    pikaVM_runSingleFile(pikaMain, "test/python/builtins/encode_decode.py");
    /* collect */
    char* b_s = obj_getStr(pikaMain, "b_s");
    uint8_t* s_b = obj_getBytes(pikaMain, "s_b");
    /* assert */
    EXPECT_STREQ(b_s, "test");
    EXPECT_EQ(s_b[0], 't');
    EXPECT_EQ(s_b[1], 'e');
    EXPECT_EQ(s_b[2], 's');
    EXPECT_EQ(s_b[3], 't');
    /* deinit */
    obj_deinit(pikaMain);
}
#endif

#if PIKA_FILEIO_ENABLE
TEST(stddata, fileio) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    pikaVM_runSingleFile(pikaMain, "test/python/builtins/file.py");
    Arg* s = obj_getArg(pikaMain, "s");
    Arg* b = obj_getArg(pikaMain, "b");
    /* assert */
    EXPECT_EQ(arg_getType(s), ARG_TYPE_STRING);
    EXPECT_EQ(arg_getType(b), ARG_TYPE_BYTES);
    /* deinit */
    obj_deinit(pikaMain);
}
#endif

#if !PIKA_NANO_ENABLE
TEST(list, in) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "a = [1, 2, 3]\n"
            "if 1 in a:\n"
            "    print('1 in a')\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "1 in a\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(dict, in) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "if \"a\" in {\"a\":1, \"b\":2}:\n"
            "    print('a in dict')\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "a in dict\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(list, slice) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "[1, 2, 3, 4][0:2]\n"
            "(5, 6, 7, 8)[1:4]\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "(6, 7, 8)\r\n");
    EXPECT_STREQ(log_buff[1], "[1, 2]\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

#endif

#if !PIKA_NANO_ENABLE
TEST(str, split) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, "'test,test'.split(',')\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "['test', 'test']\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(str, split2) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "s = 'test,test'\n"
            "s.split(',')\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "['test', 'test']\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(dict, cmodule) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "s = GTestTask.test_dict()\n"
            "print(s)");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "{'para1': 1, 'para2': 2}\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(dict, items) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "d = {'a':1, 'b':2}\n"
            "print(d.items())\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "dict_items([('a', 1), ('b', 2)])\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(dict, items2) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "d = {'a':1, 'b':2}\n"
            "for i in d.items():\n"
            "    print(i)\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[2], "BEGIN\r\n");
    EXPECT_STREQ(log_buff[1], "('a', 1)\r\n");
    EXPECT_STREQ(log_buff[0], "('b', 2)\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(dict, items_kv) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "d = {'a':1, 'b':2}\n"
            "for k, v in d.items():\n"
            "    print(k, v)\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "b 2\r\n");
    EXPECT_STREQ(log_buff[1], "a 1\r\n");
    EXPECT_STREQ(log_buff[2], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, list_str) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, "list('test')");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "['t', 'e', 's', 't']\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, list_bytes) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, "list(b'test')");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "[116, 101, 115, 116]\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, bytes_list) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, "bytes([1,2,3,4])");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "b'\\x01\\x02\\x03\\x04'\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, list_pop_) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "l = [1,2,3,4]\n"
            "l.pop()\n"
            "l.pop()\n"
            "l");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "[1, 2]\r\n");
    EXPECT_STREQ(log_buff[1], "3\r\n");
    EXPECT_STREQ(log_buff[2], "4\r\n");
    EXPECT_STREQ(log_buff[3], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, list_pop_index) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "l = [1,2,3,4]\n"
            "l.pop(2)\n"
            "l.pop(0)\n"
            "l");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "[2, 4]\r\n");
    EXPECT_STREQ(log_buff[1], "1\r\n");
    EXPECT_STREQ(log_buff[2], "3\r\n");
    EXPECT_STREQ(log_buff[3], "BEGIN\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, list_remove_) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "l = [1,2,3,4,5]\n"
            "l.remove(2)\n"
            "l\n"
            "l.remove(3)\n"
            "l");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[1], "[1, 3, 4, 5]\r\n");
    EXPECT_STREQ(log_buff[0], "[1, 4, 5]\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, list_insert_) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "l = [1,2,3]\n"
            "l.insert(1, 'q')\n"
            "l");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[1], "BEGIN\r\n");
    EXPECT_STREQ(log_buff[0], "[1, 'q', 2, 3]\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, dict_update) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "d = {'a':1, 'b':2, 'c':3}\n"
            "d.update({'b':4, 'd':5})\n"
            "res1 = d['b']\n"
            "res2 = d['a']\n"
            "print(d)\n");
    /* collect */
    /* assert */
    EXPECT_EQ(obj_getInt(pikaMain, "res1"), 4);
    EXPECT_EQ(obj_getInt(pikaMain, "res2"), 1);
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(issue, id_test) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    pikaVM_runSingleFile(pikaMain, "test/python/issue/issue_id_test.py");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "dog2 eat...\r\n");
    EXPECT_STREQ(log_buff[3], "dog1 eat...\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(str, strip) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, "s1 = 'test$'.strip('$')");
    /* collect */
    /* assert */
    char* s1 = obj_getStr(pikaMain, "s1");
    EXPECT_STREQ(s1, "test");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(str, big_slice) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    pikaVM_runSingleFile(pikaMain, "test/python/issue/issue_big_str_slice.py");
    /* collect */
    /* assert */
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(std, eval) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, "eval('1+1')");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "2\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, kw_fun) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "def test(**kw):\n"
            "    print(kw)\n"
            "test(a=1, b=2)\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "{'177670': 1, '177671': 2}\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, kw_fun_err_input) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "def test(**kw):\n"
            "    print(kw)\n"
            "test({'a':1, 'b':2})\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "{}\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, bytes_add) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain, "b'a' + b'b'\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "b'\\x61\\x62'\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, pikafs_open) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    extern unsigned char pikaModules_py_a[];
    obj_linkLibrary(pikaMain, pikaModules_py_a);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "f = open('/pikafs/widget_config.ini','r')\n"
            "f.read(8)\n"
            "f.close()\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "'[端口]'\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, pikafs_open_err) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    extern unsigned char pikaModules_py_a[];
    obj_linkLibrary(pikaMain, pikaModules_py_a);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "f = open('/pikafs/_no_file_widget_config.ini','r')\n"
            "f.read(8)\n"
            "f.close()\n");
    /* collect */
    /* assert */
    // EXPECT_STREQ(log_buff[0], "'[端口]'\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, list_slice_issue) {
    /* init */
    g_PikaMemInfo.heapUsedMax = 0;
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    /* run */
    __platform_printf("BEGIN\r\n");
    obj_run(pikaMain,
            "l = [1,2,3]\n"
            "l[-1]\n");
    /* collect */
    /* assert */
    EXPECT_STREQ(log_buff[0], "3\r\n");
    /* deinit */
    obj_deinit(pikaMain);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, New_pikaDictFromVarArgs) {
    PikaObj* new_dict =
        New_pikaDictFromVarArgs(arg_newStr("a"), arg_newInt(1), arg_newStr("b"),
                                arg_newInt(2), arg_newStr("c"), arg_newInt(3));
    pika_platform_printf("%s\r\n", PikaStdData_Dict___str__(new_dict));
    obj_deinit(new_dict);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, New_pikaDictFromVarArgs0) {
    PikaObj* new_dict = New_pikaDictFromVarArgs(NULL);
    pika_platform_printf("%s\r\n", PikaStdData_Dict___str__(new_dict));
    obj_deinit(new_dict);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, New_pikaListFromVarArgs0) {
    PikaObj* new_list = New_pikaListFromVarArgs(NULL);
    pika_platform_printf("%s\r\n", PikaStdData_List___str__(new_list));
    obj_deinit(new_list);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, NewPikaDict) {
    PikaDict* dict = New_PikaDict();
    ASSERT_NE(dict, nullptr);
    pikaDict_deinit(dict);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, SetGetInt) {
    PikaDict* dict = New_PikaDict();
    EXPECT_EQ(pikaDict_setInt(dict, "testKey", 12345), PIKA_RES_OK);
    EXPECT_EQ(pikaDict_getInt(dict, "testKey"), 12345);
    pikaDict_deinit(dict);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, SetGetFloat) {
    PikaDict* dict = New_PikaDict();
    EXPECT_EQ(pikaDict_setFloat(dict, "testFloatKey", 12.34f), PIKA_RES_OK);
    EXPECT_FLOAT_EQ(pikaDict_getFloat(dict, "testFloatKey"), 12.34f);
    pikaDict_deinit(dict);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, SetGetStr) {
    PikaDict* dict = New_PikaDict();
    EXPECT_EQ(pikaDict_setStr(dict, "testStringKey", "Hello"), PIKA_RES_OK);
    EXPECT_STREQ(pikaDict_getStr(dict, "testStringKey"), "Hello");
    pikaDict_deinit(dict);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, SetGetPtr) {
    PikaDict* dict = New_PikaDict();
    int data = 100;
    EXPECT_EQ(pikaDict_setPtr(dict, "testPtrKey", &data), PIKA_RES_OK);
    EXPECT_EQ(*reinterpret_cast<int*>(pikaDict_getPtr(dict, "testPtrKey")),
              data);
    pikaDict_deinit(dict);
    EXPECT_EQ(pikaMemNow(), 0);
}

TEST(stddata, SetGetBytes) {
    PikaDict* dict = New_PikaDict();
    uint8_t bytes[] = {0x01, 0x02, 0x03};
    EXPECT_EQ(pikaDict_setBytes(dict, "testByteKey", bytes, sizeof(bytes)),
              PIKA_RES_OK);
    EXPECT_EQ(
        memcmp(pikaDict_getBytes(dict, "testByteKey"), bytes, sizeof(bytes)),
        0);
    EXPECT_EQ(pikaDict_getBytesSize(dict, "testByteKey"), sizeof(bytes));
    pikaDict_deinit(dict);
    EXPECT_EQ(pikaMemNow(), 0);
}

#endif

TEST_END
