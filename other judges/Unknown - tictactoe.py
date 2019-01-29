def win():
    # Horizontal
    for row in board:
        if row[0] == row[1] == row[2] and row[0] != ' ':
            return row[0]
    
    # Vertical
    for i in range(3):
        if board[0][i] == board[1][i] == board[2][i] and board[2][i] != ' ':
            return board[0][i]
    
    # Diagonal
    if board[0][0] == board[1][1] == board[2][2] and board[0][0] != ' ':
        return board[0][0]
    
    if board[0][2] == board[1][1] == board[2][0] and board[1][1] != ' ':
        return board[1][1]
    
    return False

def get_valid(prompt):
    x, y = -1, -1
    while x < 0 or x > 2 or y < 0 or y > 2 or board[x][y] != ' ':
        x, y = map(int, input(prompt).split())
    
    return x, y

def display():
    print('------\n'.join(['|'.join(row) + '\n' for row in board]))

print('Welcome to tic tac toe!')

quit = False
XO = ['X', 'O']

while not quit:
    board = [[' '] * 3 for _ in range(3)]
    filled = 0

    display()

    while filled < 9:
        player = XO[filled % 2]
        playernum = filled % 2 + 1
        x, y = get_valid('Input coords for player %d (%s): ' % (playernum, player))

        board[x][y] = player
        display()

        if win() == player:
            print('%s is the winner!' % player)
            break

        filled += 1
    
    if filled == 9:
        state = win()
        if state:
            print('%s is the winner!' % state)
        else:
            print('Cats game!')
    
    quit = input('Play again? (y/n): ') != 'y'