import inspect
import sys

'''
After his fall from grace at the past year’s CCC, AQT felt that something inside him was broken,
but he was still human. He still needed to pee. And he had been holding it in for far too long.
But when he opened the door of the bathroom, the sight of the boy standing before him, arms crossed,
that familiar smirk on his face, made him shudder involuntarily.

“Jonathan, please, not today,” he said, the desperation evident in his voice,
“I really need to urinate.”  But the one in front of him just continued smiling. Not a trace of
mercy could be found in his dark eyes. "You think you can relieve yourself without my permission?”

AQT’s heart couldn’t help but skip a beat at the domineering masculinity radiating from the man who
was now walking toward him slowly, blocking all routes to the urinals.

Then Jonathan was close. So close AQT could smell him. The strong, musky scent of unwashed gym shirts
made his knees go weak, and he fell to the sordid floor of the high school lavatory.

Jonathan ruthlessly grabbed AQT by the chin and tilted his face up.

“What do you need to do?” he demanded, “Why don’t you repeat it!”

“Please, Jonathan, just let me use the washroom. Today we write the CCC again, and I don’t want to waste
my chance to rectify the past. If you don’t let me go now, I really will have to change my pants, and
then I won’t have time to finish the nasty implementation problem that is sure to rear its ugly head.”

Rage distorted Jonathan’s features. “YOUR FACE IS A NASTY IMPLEMENTATION PROBLEM!” he cried, punching
the kneeling boy hard in the face. He hit him again and again, until the body in his hands fell limply
to the floor.

His cathartic fit having run its course, Jonathan looked at the bloodied, unconscious figure with
something akin to regret. The sight of its muscles, hardened from so much fortnite dancing, moved
something deep in his chest.

“Don’t worry,” he whispered, brushing strands of matted hair off AQT’s face, “I will reach CCO for both
of us. Then, you will have no choice but to be mine. Give up on Joey. I will always want you.”

With that, he laid the body down gently, and left the washroom to write CCC and make good on his vow.
'''

def main():
    # Have to account for unix vs windows
    modulename = sys.argv[0]
    if modulename.count('\\'):
        modulename = modulename.split('\\')[-1].split('.')[0]
    else:
        modulename = modulename.split('/')[-1].split('.')[0]
    
    module = __import__(modulename)
    print(inspect.getsource(module))

if __name__ == '__main__':
    main()