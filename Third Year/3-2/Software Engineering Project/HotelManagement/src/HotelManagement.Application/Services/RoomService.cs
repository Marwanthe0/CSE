using HotelManagement.Application.DTOs.Rooms;
using HotelManagement.Application.Interfaces;
using HotelManagement.Domain.Entities;
using HotelManagement.Application.DTOs.Rooms;

namespace HotelManagement.Application.Services;

public class RoomService : IRoomService
{
    private readonly IRoomRepository _roomRepository;

    public RoomService(IRoomRepository roomRepository)
    {
        _roomRepository = roomRepository;
    }

    public async Task<IEnumerable<Room>> GetAllRoomsAsync()
    {
        return await _roomRepository.GetAllAsync();
    }

    public async Task<Room?> GetRoomByIdAsync(int id)
    {
        return await _roomRepository.GetByIdAsync(id);
    }


    public async Task AddRoomAsync(CreateRoomDTO dto)
    {
        var room = new Room
        {
            RoomNumber = dto.RoomNumber,
            RoomType = dto.RoomType,
            PricePerNight = dto.PricePerNight,
            IsAvailable = dto.IsAvailable
        };

        await _roomRepository.AddAsync(room);
    }


    public async Task UpdateRoomAsync(int id,UpdateRoomDto dto)
    {
        var room = await _roomRepository.GetByIdAsync(id);
        if (room == null)
        {
            return;
        }
        
        room.RoomNumber = dto.RoomNumber;
        room.RoomType = dto.RoomType;
        room.PricePerNight = dto.PricePerNight;
        room.IsAvailable = dto.IsAvailable;
        
        await _roomRepository.UpdateAsync(room);
    }

    public async Task DeleteRoomAsync(int id)
    {
        var room = await _roomRepository.GetByIdAsync(id);
        if(room != null)
        {
            await _roomRepository.DeleteAsync(room);
        }
    }
}