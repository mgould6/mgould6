using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Chess;

    public class Move
    {
        public ChessPiece Piece { get; set; }
        public int FromColumn { get; set; }
        public int FromRow { get; set; }
        public int ToColumn { get; set; }
        public int ToRow { get; set; }

        public Move(ChessPiece piece, int fromColumn, int fromRow, int toColumn, int toRow)
        {
            Piece = piece;
            FromColumn = fromColumn;
            FromRow = fromRow;
            ToColumn = toColumn;
            ToRow = toRow;
        }
    }
