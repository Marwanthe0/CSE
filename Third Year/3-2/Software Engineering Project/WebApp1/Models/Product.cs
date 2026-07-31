namespace WebApp1.Models
{
    public class Product
    {
        public int Id { get; set; }
        public required string Name { get; set; }
        public Category? Category { get; set; }
        public int CategoryId { get; set; }
        public DateOnly ReleaseDate { get; set; }
    }
}
