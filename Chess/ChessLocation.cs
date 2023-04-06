namespace ChessGame
{
    public class ChessLocation
    {
        public int Row { get; set; }
        public int Column { get; set; }

        public ChessLocation(int row, int col)
        {
            Row = row;
            Column = col;
        }

        public override string ToString()
        {
            char columnChar = (char)('A' + Column);
            return $"{columnChar}{8 - Row}";
        }
    }
}
