using System.Collections.Generic;
using Chess;

public class Pawn : ChessPiece
{
    public Pawn(int column, int row, bool isWhite) : base(column, row, isWhite)
    {
    }

    public override List<Move> GetValidMoves(ChessBoard board)
    {
        List<Move> validMoves = new List<Move>();

        // Calculate the direction the pawn can move based on its color
        int direction = IsWhite ? -1 : 1;

        // Check if the pawn can move one square forward
        ChessPiece forwardPiece = board.GetPieceAt(Column, Row + direction);
        if (forwardPiece == null)
        {
            validMoves.Add(new Move(this, Column, Row, Column, Row + direction));

            // Check if the pawn can move two squares forward (only from its starting position)
            if ((IsWhite && Row == 6) || (!IsWhite && Row == 1))
            {
                ChessPiece forwardTwoPiece = board.GetPieceAt(Column, Row + (direction * 2));
                if (forwardTwoPiece == null)
                {
                    validMoves.Add(new Move(this, Column, Row, Column, Row + (direction * 2)));
                }
            }
        }

        // Check if the pawn can capture diagonally (left and right)
        for (int i = -1; i <= 1; i += 2)
        {
            ChessPiece diagonalPiece = board.GetPieceAt(Column + i, Row + direction);
            if (diagonalPiece != null && diagonalPiece.IsWhite != IsWhite)
            {
                validMoves.Add(new Move(this, Column, Row, Column + i, Row + direction));
            }
        }

        // Add en passant logic here if desired

        return validMoves;
    }

}