#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int TRACE_SIZE = 1024;
void backtrace()
{

        void *buffer[TRACE_SIZE];
        char **strings;
        int nptrs;
        nptrs = backtrace((void **)buffer, TRACE_SIZE);
        strings = backtrace_symbols((void **)buffer, nptrs);
        //buff_err("[TransFormer-->]======size: %u=====\n", info->size);
        for (int i = 0; i < nptrs; ++i) {
            printf("%s\n",strings[i]);
        }
        free(strings);


}
void testaa()
{
 backtrace();

}

void testbbb()
{
 testaa();

}
int main()
{

    int pageSize = sysconf(_SC_PAGE_SIZE);
    if (pageSize == -1) {
        perror("sysconf fail");
        return -1;
    }
    char mbuf[4096];
    printf("One Page Size is:%d Byte\r\n", pageSize);
    char *p = mbuf;
    int ret = posix_memalign((void**)&p, pageSize, pageSize);
    if (ret != 0) {
        printf("posix_memalign fail, ret %u\r\n", ret);
        return -1;
    }
    testbbb();
    printf("posix_memalign mem %p\r\n", mbuf);
    p[100] = 0x0F; // 结果写入
    printf("before protect,write the value 0x%x\n,Success!",p[100]);
    ret = mprotect(p, pageSize, PROT_READ);
    if (ret == -1) {
        perror("mprotect");
        return -1;
    }
    p[100] = 1; //结果写入，预期会崩
    printf("the g_ps32Result is %d\n", p[100]);
    return 0;
}

