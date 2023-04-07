using System.Collections.Generic;

public abstract class ChessPiece
{
    public int Column { get; set; }
    public int Row { get; set; }
    public bool IsWhite { get; set; }

    public ChessPiece(int column, int row, bool isWhite)
    {
        Column = column;
        Row = row;
        IsWhite = isWhite;
    }

    public abstract List<Move> GetValidMoves(ChessBoard board);
}