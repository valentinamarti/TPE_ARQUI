#include <regsuser.h>
#include <lib.h>

// Container defines
#define NAMER "REGISTERS_DUMP"
#define CX0R 275 //Constant X0
#define CY0R 100 //Constant Y0
#define WIDTHR 450
#define HEIGHTR 580

// Container defines
#define NAMEE "ERROR_CONTAINER"
#define CX0E 275 //Constant X0
#define CY0E 200 //Constant Y0
#define WIDTHE 500
#define HEIGHTE 100

static char *regsNames[] = {"RAX <> ", "RBX <> ", "RCX <> ", "RDX <> ", "RSI <> ", "RDI <> ", "RBP <> ", "RSP <> ", "R8  <> ", "R9  <> ", "R10 <> ", "R11 <> ", "R12 <> ", "R13 <> ", "R14 <> ", "R15 <> ", "RIP <> "};
static int container_id;

void run_regsuser(){
    uint64_t registers[17] = {0};
    int flag = do_sys_get_registers(registers);

    if(flag == 1){
        container_id = do_sys_new_container(NAMER,CX0R,CY0R,WIDTHR,HEIGHTR); 
        set_container_id(container_id);
        setFontSize(2);
        setBackground(REGISTERS_DUMP_BACKGROUND);
        setBorder(REGISTERS_DUMP_BORDER);    
        
        print("Registers dump \n", REGISTERS_DUMP_TITTLE);

        for (int i = 0; i < 17; i++){		
            printf(" %s ", REGISTERS_DUMP_REGS, regsNames[i]);
            printf(" %x \n", REGISTERS_DUMP_LETTER, registers[i]);
        }
        char c;
        while(c = getCharFromKernel()!= ESCAPE){}
        exitContainer(container_id);
    }else{
        container_id = do_sys_new_container(NAMEE,CX0E,CY0E,WIDTHE,HEIGHTE); 
        set_container_id(container_id);
		setFontSize(2);
		setBackground(REGISTERS_DUMP_BACKGROUND);
		setBorder(REGISTERS_DUMP_BORDER);

        newLine(container_id);
		print("Error, no registers were saved \n", ERROR_REGISTERS_DUMP);
		sleep(5000);
		exitContainer(container_id);
    }
}
