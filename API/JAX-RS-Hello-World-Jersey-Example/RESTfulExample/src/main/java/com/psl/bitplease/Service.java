package com.psl.bitplease;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.core.Response;

@Path("/")
public class Service {

	private static String FILE_NAME = "fileLocation.txt";

	@GET
	@Path("/{param}")
	public Response enqueue(@PathParam("param") String msg) throws IOException {
		try {
			ClassLoader classLoader = getClass().getClassLoader();
			File file = new File(classLoader.getResource(FILE_NAME).getFile());
			Scanner sc = new Scanner(file);
			FileWriter file2 = new FileWriter(sc.nextLine(), Boolean.TRUE);
			file2.write(msg + ",");
			file2.flush();
			file2.close();
			sc.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return Response.status(200).entity("").build();
	}

	@GET
	@Path("/gesture")
	public Response print() throws FileNotFoundException {

		try {
			ClassLoader classLoader = getClass().getClassLoader();
			File file1 = new File(classLoader.getResource(FILE_NAME).getFile());
			Scanner sc1 = new Scanner(file1);
			String file_path = sc1.nextLine();
			Scanner sc = new Scanner(new File(file_path));
			String line = null;
			if (sc.hasNextLine()) {
				line = sc.nextLine();
			} else {
				sc.close();
				return Response.status(200).entity("").build();
			}
			String[] splited = line.split(",");
			List<String> strings = Arrays.asList(splited);
			String returnvalue = strings.get(0);
			sc.close();

			FileWriter file = new FileWriter(file_path, Boolean.FALSE);
			line = line.replaceFirst(strings.get(0) + ",", "");
			file.write(line);
			file.flush();
			file.close();

			return Response.status(200).entity(returnvalue).build();
		} catch (Throwable e) {
			e.printStackTrace();
			return Response.status(404).entity("").build();
		}

	}
}