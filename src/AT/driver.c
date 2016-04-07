/* The authors of this work have released all rights to it and placed it
in the public domain under the Creative Commons CC0 1.0 waiver
(http://creativecommons.org/publicdomain/zero/1.0/).

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Turing_machine_simulator_(C)?oldid=10481
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tm.h"

struct turing_machine get_example_turing_machine(void) {
    struct turing_machine machine;
    int i, j;
    machine.initial_control_state = 0;
    machine.blank_symbol = '#';
    machine.num_accepting_states = 1;
    machine.accepting_states = malloc(sizeof(int)*machine.num_accepting_states);
    if (machine.accepting_states == NULL) {
        printf("Out of memory");
        exit(-1);
    }
    machine.accepting_states[0] = 5;
    #define NUM_STATES 7
    #define STATE_INVALID 6

    machine.transition_table = malloc(sizeof(struct transition_result *) * NUM_STATES);
    if (machine.transition_table == NULL) {
        printf("Out of memory");
        exit(-1);
    }
    for (i=0; i<NUM_STATES; i++) {
        machine.transition_table[i] =
            malloc(sizeof(struct transition_result)*TAPE_ALPHABET_SIZE);
        if (machine.transition_table[i] == NULL) {
            printf("Out of memory");
            exit(-1);
        }
        for (j=0; j<TAPE_ALPHABET_SIZE; j++) {
            machine.transition_table[i][j].control_state = STATE_INVALID;
            machine.transition_table[i][j].write_symbol = machine.blank_symbol;
            machine.transition_table[i][j].dir = DIR_LEFT;
        }
    }
    machine.transition_table[0]['#'].control_state = 4;
    machine.transition_table[0]['#'].write_symbol  = '#';
    machine.transition_table[0]['#'].dir           = DIR_RIGHT;

    machine.transition_table[0]['a'].control_state = 1;
    machine.transition_table[0]['a'].write_symbol  = '#';
    machine.transition_table[0]['a'].dir           = DIR_RIGHT;

    machine.transition_table[4]['#'].control_state = 5;
    machine.transition_table[4]['#'].write_symbol  = '#';
    machine.transition_table[4]['#'].dir           = DIR_RIGHT;

    machine.transition_table[1]['a'].control_state = 1;
    machine.transition_table[1]['a'].write_symbol  = 'a';
    machine.transition_table[1]['a'].dir           = DIR_RIGHT;

    machine.transition_table[1]['b'].control_state = 1;
    machine.transition_table[1]['b'].write_symbol  = 'b';
    machine.transition_table[1]['b'].dir           = DIR_RIGHT;

    machine.transition_table[1]['#'].control_state = 2;
    machine.transition_table[1]['#'].write_symbol  = '#';
    machine.transition_table[1]['#'].dir           = DIR_LEFT;

    machine.transition_table[2]['b'].control_state = 3;
    machine.transition_table[2]['b'].write_symbol  = '#';
    machine.transition_table[2]['b'].dir           = DIR_LEFT;

    machine.transition_table[3]['a'].control_state = 3;
    machine.transition_table[3]['a'].write_symbol  = 'a';
    machine.transition_table[3]['a'].dir           = DIR_LEFT;

    machine.transition_table[3]['b'].control_state = 3;
    machine.transition_table[3]['b'].write_symbol  = 'b';
    machine.transition_table[3]['b'].dir           = DIR_LEFT;

    machine.transition_table[3]['#'].control_state = 0;
    machine.transition_table[3]['#'].write_symbol  = '#';
    machine.transition_table[3]['#'].dir           = DIR_RIGHT;
    return machine;
}

int main(int argc, char* argv[]) {
    if (argc < 1 + 1) {
        printf("Syntax: simulate_turing_machine <input string>\n");
        return -1;
    }
    simulate(get_example_turing_machine(), strlen(argv[1]), argv[1]);
    return 0;
}
