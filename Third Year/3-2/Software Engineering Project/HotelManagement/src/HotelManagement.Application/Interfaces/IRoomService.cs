using HotelManagement.Application.DTOs.Rooms;
using HotelManagement.Domain.Entities;

namespace HotelManagement.Application.Interfaces;

public interface IRoomService
{
    Task<IEnumerable<Room>> GetAllRoomsAsync();

    Task<Room?> GetRoomByIdAsync(int id);

    Task AddRoomAsync(CreateRoomDTO room);

    Task UpdateRoomAsync(int id,UpdateRoomDto room);

    Task DeleteRoomAsync(int id);
}