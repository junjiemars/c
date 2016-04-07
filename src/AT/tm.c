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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tm.h"

struct turing_machine_state {
    int control_state;
    int head_position;
    int tape_size;
    symbol* tape;
}; /* This structure need not be public */
struct turing_machine_state
create_initial_state(int initial_control_state, int input_string_length, symbol* input_string) {
    struct turing_machine_state state;
    state.control_state = initial_control_state;
    state.head_position = 0; /* Initially at left end */
    state.tape_size = input_string_length;
    state.tape = malloc(sizeof(symbol)*input_string_length);
    if (state.tape == NULL) {
        printf("Out of memory");
        exit(-1);
    }

    memmove(state.tape, input_string, sizeof(symbol)*input_string_length);
    return state;
}
void free_state(struct turing_machine_state* state) {
    free(state->tape);
}
void update_state(struct turing_machine_state* state, int new_control_state,
                  enum direction dir, char write_symbol, char blank_symbol)
{
    state->control_state = new_control_state;
    state->tape[state->head_position] = write_symbol;
    if (dir == DIR_LEFT && state->head_position > 0) {
        state->head_position--;
    } else { /* dir == DIR_RIGHT */
        state->head_position++;
    }
    if (state->head_position >= state->tape_size) {
        int i, old_tape_size = state->tape_size;
        symbol* new_tape = realloc(state->tape, old_tape_size*2 + 10);
        if (new_tape == NULL) {
            printf("Out of memory");
            exit(-1);
        }
        state->tape = new_tape;
        state->tape_size *= 2;
        for (i=old_tape_size; i < state->tape_size; i++) {
            state->tape[i] = blank_symbol;
        }
    }
}
void trace_state(struct turing_machine_state* state, symbol blank_symbol) {
    int i;
    for(i=0; i < TRACE_TAPE_CHARS && i < state->head_position; i++) {
        printf(" ");
    }
    if (i < TRACE_TAPE_CHARS) {
        printf("v"); /* points down */
    }
    printf("\n");
    for(i=0; i < TRACE_TAPE_CHARS; i++) {
        printf("%c", i < state->tape_size ? state->tape[i] : blank_symbol);
    }
    printf("\n");
}


int is_in_int_list(int value, int list_size, int list[]) {
    int i;
    for(i=0; i<list_size; i++) {
        if (list[i] == value) {
            return 1;
        }
    }
    return 0;
}
void simulate(struct turing_machine machine, int input_string_length, symbol* input_string) {
    struct turing_machine_state state =
        create_initial_state(machine.initial_control_state, input_string_length, input_string);
    trace_state(&state, machine.blank_symbol);

    while (!is_in_int_list(state.control_state, machine.num_accepting_states,
                           machine.accepting_states)) {
        struct transition_result next =
            machine.transition_table[state.control_state]
                                    [(int)state.tape[state.head_position]];
        update_state(&state, next.control_state, next.dir,
                     next.write_symbol, machine.blank_symbol);
        trace_state(&state, machine.blank_symbol);
    }
    free_state(&state);
}

