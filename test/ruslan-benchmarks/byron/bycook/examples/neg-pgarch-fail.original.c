// #include "ctl.h"

// Property: G F wakened==1

int wakend;
unsigned int pc;
int __phi() { return CEF(CEG(CAP(wakend != 1))); }

/*
 * pgarch_MainLoop
 *
 * Main loop for archiver
 */
int          last_copy_time = 0;
int          curtime;
#define true 1
#define false 0
#define NULL 0
#define PGC_SIGHUP 1
int got_SIGHUP;
void init() {
  wakend = 1; got_SIGHUP = nondet();
}

int __rho_1_;


void ProcessConfigFile(int a) {}
int XLogArchivingActive() { 
  __rho_1_ = nondet();
return __rho_1_;
}
void pgarch_ArchiverCopyLoop() { }
int time(int a) { return nondet(); }
void pg_usleep(int a) {}
#define PGARCH_AUTOWAKE_INTERVAL 1000
int PostmasterIsAlive(int a) { return nondet(); }

void body() {

        /*
         * We run the copy loop immediately upon entry, in case there are
         * unarchived files left over from a previous database run (or maybe
         * the archiver died unexpectedly).  After that we wait for a signal
         * or timeout before doing more.
         */
        wakend = true;

        while(1)
        {
                /* Check for config update */
                if (got_SIGHUP>0)
                {
                        got_SIGHUP = 0;
                        ProcessConfigFile(PGC_SIGHUP);
			int tt = XLogArchivingActive();
			  if (tt<=0)
                                break;                  /* user wants us to shut down */
                }
                /* Do what we're here for */
                if (wakend>0)
                {
                        wakend = 0;
                        pgarch_ArchiverCopyLoop();
                        last_copy_time = time(NULL);
                }
                /*
                 * There shouldn't be anything for the archiver to do except to
                 * wait for a signal, ... however, the archiver exists to
                 * protect our data, so she wakes up occasionally to allow
                 * herself to be proactive. In particular this avoids getting
                 * stuck if a signal arrives just before we sleep.
                 */
                if (wakend<=0)
                {
		  //pg_usleep(PGARCH_AUTOWAKE_INTERVAL * 1000000L);

                        curtime = time(NULL);
                        if ((curtime - last_copy_time) >=
			     PGARCH_AUTOWAKE_INTERVAL)
                                wakend = true;
                }
		dummy =  PostmasterIsAlive(true);
		if (dummy<=0) { break; }
        }

	while(1) { wakend = 1; dummy=dummy; } L_return: return 0;
}

int main() {}
