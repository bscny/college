#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <err.h>
#include <execinfo.h>

#define MAX_STACK_FRAMES 16

static void posix_print_stack_trace(void)
{
	int i, trace_size = 0;
    void *trace[MAX_STACK_FRAMES];
    char **messages = (char **)NULL;

    trace_size = backtrace(trace, MAX_STACK_FRAMES);
    /* overwrite sigaction with caller's address */
    messages = backtrace_symbols(trace, trace_size);
    /*
	skip the first couple stack frames (as they are this function and
    our handler) and also skip the last frame as it's (always?) junk.
	*/
    printf("dump backtrace ...\n");
    for (i = 0; i < trace_size; ++i) // we'll use this for now so you can see what's going on
    {
        printf("  [%02d] %s\n", i, messages[i]);
    }
    if (messages) 
    { 
        free(messages); 
    }
    printf("\n");
}

static char *posix_signal_num_to_txt(int signo, siginfo_t *siginfo)
{
    switch(signo)
    {
        case SIGSEGV: return "segmentation fault";
        case SIGINT: return "interactive attention signal";
        case SIGFPE:
            switch(siginfo->si_code)
            {
                case FPE_INTDIV: return "divide by zero";
                case FPE_INTOVF: return "integer overflow";
                case FPE_FLTDIV: return "floating-point divide by zero";
                case FPE_FLTOVF: return "floating-point overflow";
                case FPE_FLTUND: return "floating-point underflow";
                case FPE_FLTRES: return "floating-point inexact result";
                case FPE_FLTINV: return "floating-point invalid operation";
                case FPE_FLTSUB: return "subscript out of range";
                default: return "unknown signal of SIGFPE";
            }
        case SIGILL:
            switch(siginfo->si_code)
            {
                case ILL_ILLOPC: return "illegal opcode";
                case ILL_ILLOPN: return "illegal operand";
                case ILL_ILLADR: return "illegal addressing mode";
                case ILL_ILLTRP: return "illegal trap";
                case ILL_PRVOPC: return "privileged opcode";
                case ILL_PRVREG: return "privileged register";
                case ILL_COPROC: return "coprocessor error";
                case ILL_BADSTK: return "internal stack error";
                default: return "Illegal Instruction";
            }
        case SIGTERM: return "termination request";
        case SIGABRT: return "caused by an abort() or assert()";
        default: return "unknown signal";
    }
}

static void posix_signal_handler(int signo, siginfo_t *siginfo, void *context)
{
    printf("\n##### OPPS: receive signal %s #####\n", posix_signal_num_to_txt(signo, siginfo));
    posix_print_stack_trace();
    //signal(signo, SIG_DFL);
    //raise(signo);
    exit(1);
}

void set_signal_handler(void)
{
    /* register my signal handlers */
    struct sigaction sig_action = {};
    sig_action.sa_sigaction = posix_signal_handler;
    sigemptyset(&sig_action.sa_mask);
    sig_action.sa_flags = SA_SIGINFO | SA_ONSTACK;
    //sig_action.sa_flags = SA_RESTART;

    if (sigaction(SIGSEGV, &sig_action, NULL) != 0) { err(1, "sigaction"); }
    if (sigaction(SIGFPE,  &sig_action, NULL) != 0) { err(1, "sigaction"); }
    if (sigaction(SIGINT,  &sig_action, NULL) != 0) { err(1, "sigaction"); }
    if (sigaction(SIGILL,  &sig_action, NULL) != 0) { err(1, "sigaction"); }
    if (sigaction(SIGTERM, &sig_action, NULL) != 0) { err(1, "sigaction"); }
    if (sigaction(SIGABRT, &sig_action, NULL) != 0) { err(1, "sigaction"); }
}
