using System.Collections.Generic;
using Chess;

public class Queen : ChessPiece
{
    public Queen(int column, int row, bool isWhite) : base(column, row, isWhite)
    {
    }

    public override List<Move> GetValidMoves(ChessBoard board)
    {
        List<Move> validMoves = new List<Move>();

        // Check moves in each direction (horizontal, vertical, and diagonal)
        for (int dColumn = -1; dColumn <= 1; dColumn++)
        {
            for (int dRow = -1; dRow <= 1; dRow++)
            {
                if (dColumn == 0 && dRow == 0) continue; // Skip the current position
                AddMovesInDirection(validMoves, board, dColumn, dRow);
            }
        }

        return validMoves;
    }

    private void AddMovesInDirection(List<Move> validMoves, ChessBoard board, int dColumn, int dRow)
    {
        for (int distance = 1; distance <= 7; distance++)
        {
            int newColumn = Column + (dColumn * distance);
            int newRow = Row + (dRow * distance);
            ChessPiece targetPiece = board.GetPieceAt(newColumn, newRow);
            if (targetPiece == null)
            {
                validMoves.Add(new Move(this, Column, Row, newColumn, newRow));
            }
            else
            {
                if (targetPiece.IsWhite != IsWhite)
                {
                    validMoves.Add(new Move(this, Column, Row, newColumn, newRow));
                }
                break;
            }
        }
    }
}