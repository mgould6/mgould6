using System.Collections.Generic;
using Chess;

public class King : ChessPiece
{
    public King(int column, int row, bool isWhite) : base(column, row, isWhite)
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

                int newColumn = Column + dColumn;
                int newRow = Row + dRow;
                ChessPiece targetPiece = board.GetPieceAt(newColumn, newRow);
                if (targetPiece == null || targetPiece.IsWhite != IsWhite)
                {
                    validMoves.Add(new Move(this, Column, Row, newColumn, newRow));
                }
            }
        }

        // Add castling logic here if desired

        return validMoves;
    }

}