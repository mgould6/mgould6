using System;
using Chess;


namespace Chess
{
    public class Board
    {
        // Define your properties or fields here, for example:
        // private Piece[,] board;
        private Piece[,] board = new Piece[8, 8];
        // Now, you can add your methods inside the class:

        public Piece GetPiece(int x, int y)
        {
            // Your implementation here
            return board[x, y];
        }

        public void SetPiece(int x, int y, Piece piece)
        {
            // Your implementation here
        }

        public void RemovePiece(int x, int y)
        {
            // Your implementation here
        }

        // Add other methods or properties as needed.
    }
}
