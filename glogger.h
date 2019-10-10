#include<sstream>
#include<ostream>
#include<fstream>
#include<chrono>
#include<iomanip>
#include<optional>


class Glogger
{
	/*->$ m_is_data_buffered
		->$ m_logstream
		->$ m_logfile
	*/
	 bool m_is_data_buffered;
	 std::stringstream m_logstream;
	 std::ofstream m_logfile;

	/*->MAKE GLOGGER CONSTRUCTOR PRIVATE TO PREVENT INSTANTIATION OF OBJECT*/
	Glogger() {}
	

public:
	//->GET INSTANCE() : Returns the singleton instance of Glogger

	
	 Glogger(std::string filename, bool data_is_buffered)
	{
		m_logfile.open(filename);
		if (m_logfile.is_open())
		{
			
			m_is_data_buffered = data_is_buffered;
			
		}
		else
		{
			m_is_data_buffered = true;
			

		}
	}
	template<typename T>
	void log(const T& data, std::string func_name,std::ostream * secondary_stream)
	{
		//SET $DATE = CURRENT_DATE;
		std::string current_date=getCurrentDateOrTime("%d %m %Y"); //= //getCurrentDateOrTime("%d-%m-%Y");
		//SET $TIME = CURRENT_TIME;
		std::string current_time=getCurrentDateOrTime("%X"); //= //getCurrentDateOrTime("%X");
		std::string log_info = '[' + func_name + ':' + current_date + ' ' + current_time + ']';
		if (m_is_data_buffered)
		{
			m_logstream << log_info << data<<"\n";

		}
		else
		{
			
			m_logfile << log_info << data<<"\n";
		}
			if (secondary_stream)
		{
			*secondary_stream << log_info << data << "\n";
		}
	}
	void flush()
	{
		if (m_logfile.is_open())
		{
			m_logfile << m_logstream.str();
		}
		m_logfile.close( );
		
	}
	void flush(std::ostream& secondary_stream)
	{
		secondary_stream << m_logstream.str();
		m_logfile.close( );
	}
private:

	std::string getCurrentDateOrTime(std::string specifier)
	{
		auto current_time = std::chrono::system_clock::now();
		auto current_time_in_time_t = std::chrono::system_clock::to_time_t(current_time);
		std::tm buf;
		localtime_s(&buf, &current_time_in_time_t);
		std::stringstream date_time;
		date_time << std::put_time(&buf, specifier.c_str());
		return date_time.str();
	}
	

};