#define P_NUM 5
#define LEFT (i-1)%P_NUM
#define RIGHT (i+1)%P_NUM

typedef enum state {
    THINKING,
    HUNGRY,
    EATING
} state_t;

state_t p_state[5] = {THINKING, 
THINKING, 
THINKING, 
THINKING, 
THINKING
};