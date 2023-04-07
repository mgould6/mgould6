using System;
using System.Collections.Generic;
using Chess;

public class Knight : ChessPiece
{
    public Knight(int column, int row, bool isWhite) : base(column, row, isWhite)
    {
    }

    public override List<Move> GetValidMoves(ChessBoard board)
    {
        List<Move> validMoves = new List<Move>();

        // Check moves in each of the knight's L-shaped patterns
        int[] offsets = { -2, -1, 1, 2 };
        for (int i = 0; i < offsets.Length; i++)
        {
            for (int j = 0; j < offsets.Length; j++)
            {
                if (Math.Abs(offsets[i]) != Math.Abs(offsets[j]))
                {
                    int newColumn = Column + offsets[i];
                    int newRow = Row + offsets[j];
                    ChessPiece targetPiece = board.GetPieceAt(newColumn, newRow);
                    if (targetPiece == null || targetPiece.IsWhite != IsWhite)
                    {
                        validMoves.Add(new Move(this, Column, Row, newColumn, newRow));
                    }
                }
            }
        }

        return validMoves;
    }

}