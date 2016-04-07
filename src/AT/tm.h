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

#ifndef _SIMULATE_TURING_MACHINE_H_
#define _SIMULATE_TURING_MACHINE_H_

#define TAPE_ALPHABET_SIZE 256

#define TRACE_TAPE_CHARS   78

typedef char symbol;

enum direction { DIR_LEFT, DIR_RIGHT };

struct transition_result {
    int control_state;
    symbol write_symbol;
    enum direction dir;
};
struct turing_machine {
    int initial_control_state;
    char blank_symbol;
    int num_accepting_states;
    int* accepting_states;    
    struct transition_result** transition_table;
};
void simulate(struct turing_machine machine, int input_string_length, symbol* input_string);

#endif /* #ifndef _SIMULATE_TURING_MACHINE_H_ */

