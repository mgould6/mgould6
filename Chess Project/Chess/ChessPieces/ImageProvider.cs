using System.Drawing;
using Chess.Properties;
using ChessGame;

namespace Chess
{
    public static class ImageProvider
    {
        public static Image GetImageForPiece(ChessPiece piece)
        {
            if (piece is Pawn)
            {
                if (piece.Player == ChessPlayer.White)
                {
                    return Resources.Pawn;
                }
                else
                {
                    return Resources.Pawn2;
                }
            }
            else if (piece is Rook)
            {
                if (piece.Player == ChessPlayer.White)
                {
                    return Resources.Rook;
                }
                else
                {
                    return Resources.Rook2;
                }
            }
            else if (piece is Knight)
            {
                if (piece.Player == ChessPlayer.White)
                {
                    return Resources.Knight2;
                }
                else
                {
                    return Resources.Knight2;
                }
            }
            else if (piece is Bishop)
            {
                if (piece.Player == ChessPlayer.White)
                {
                    return Resources.Bishop;
                }
                else
                {
                    return Resources.Bishop2;
                }
            }
            else if (piece is Queen)
            {
                if (piece.Player == ChessPlayer.White)
                {
                    return Resources.Queen;
                }
                else
                {
                    return Resources.Queen2;
                }
            }
            else if (piece is King)
            {
                if (piece.Player == ChessPlayer.White)
                {
                    return Resources.King;
                }
                else
                {
                    return Resources.King2;
                }
            }
            else
            {
                return null;
            }
        }
    }
}
